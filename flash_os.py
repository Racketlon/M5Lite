import subprocess
import shutil
import os
import getpass
import tkinter as tk
from tkinter import ttk, messagebox
import time

# Define the folder to copy
FOLDER_TO_COPY = "Apps/"

def get_sd_devices():
    """
    Detects /dev/sdX devices by parsing 'lsblk' command output.
    """
    devices = []
    try:
        result = subprocess.run(['lsblk', '-o', 'NAME,SIZE,TYPE,MODEL', '-d'], stdout=subprocess.PIPE, text=True)
        for line in result.stdout.splitlines()[1:]:
            parts = line.split()
            if len(parts) >= 3 and parts[2] == 'disk' and parts[0].startswith('sd'):  # Check for /dev/sdX devices
                device = f"/dev/{parts[0]}"
                size = parts[1]
                model = " ".join(parts[3:]) if len(parts) > 3 else "Unknown"
                devices.append({"device": device, "size": size, "model": model})
    except Exception as e:
        messagebox.showerror("Error", f"Failed to detect devices: {e}")
        exit()
    return devices

def run_with_pkexec(command):
    """
    Runs a command with pkexec to elevate privileges.
    """
    try:
        subprocess.run(['pkexec'] + command, check=True)
    except subprocess.CalledProcessError as e:
        raise RuntimeError(f"Command failed: {' '.join(command)}\nError: {e}")

def format_device(device, label="M5Lite"):
    """
    Formats the device as FAT32 using mkfs.vfat and assigns a label.
    """
    try:
        # Unmount the device using udisksctl
        subprocess.run(['udisksctl', 'unmount', '--block-device', device], check=False)  # Ignore errors if already unmounted
        time.sleep(1)  # Ensure unmount completes
        # Format the device with mkfs.vfat
        run_with_pkexec(['mkfs.vfat', '-I', '-n', label, device])
    except RuntimeError as e:
        raise RuntimeError(f"Failed to format the device: {e}")

def mount_device(device):
    """
    Mounts the device using udisksctl and retrieves the mountpoint.
    """
    try:
        result = subprocess.run(['udisksctl', 'mount', '--block-device', device], stdout=subprocess.PIPE, text=True)
        for line in result.stdout.splitlines():
            if "Mounted at" in line:
                return line.split("Mounted at ")[1].strip()
        # Fallback: Check /run/media/<username>
        username = getpass.getuser()
        media_path = f"/run/media/{username}/"
        for item in os.listdir(media_path):
            item_path = os.path.join(media_path, item)
            if os.path.ismount(item_path):
                return item_path
        raise RuntimeError("Failed to retrieve mount point.")
    except Exception as e:
        raise RuntimeError(f"Failed to mount the device: {e}")

def unmount_device(device):
    """
    Unmounts the device using udisksctl.
    """
    try:
        subprocess.run(['udisksctl', 'unmount', '--block-device', device], check=False)  # Ignore errors if already unmounted
        time.sleep(1)  # Ensure unmount completes
    except subprocess.CalledProcessError as e:
        raise RuntimeError(f"Failed to unmount the device: {e}")

def flash_files(device, progress_bar, status_label):
    """
    Copies the OS files to the selected storage device.
    """
    try:
        # Format the device
        status_label.config(text=f"Formatting {device} as FAT32...")
        format_device(device)

        # Mount the device
        status_label.config(text=f"Mounting {device}...")
        mount_point = mount_device(device)
        if not mount_point:
            raise RuntimeError("Mount point is None. Failed to mount the device.")

        # Copy the entire folder to the mounted device
        status_label.config(text=f"Copying files to {device}...")
        progress_bar['value'] = 0
        progress_bar['maximum'] = 1  # Only one folder to copy

        shutil.copytree(FOLDER_TO_COPY, os.path.join(mount_point, FOLDER_TO_COPY))
        progress_bar['value'] = 1
        progress_bar.update()

        # Unmount the device
        status_label.config(text=f"Unmounting {device}...")
        unmount_device(device)

        status_label.config(text="Flash complete! OS installed successfully.")
        messagebox.showinfo("Success", "Pulse OS has been successfully flashed!")
    except RuntimeError as e:
        status_label.config(text="Flash failed.")
        messagebox.showerror("Error", str(e))
    finally:
        # Cleanup if something went wrong
        try:
            if mount_point and os.path.ismount(mount_point):
                unmount_device(device)
        except Exception:
            pass

def main():
    """
    Main GUI application for the Pulse OS Flasher.
    """
    root = tk.Tk()
    root.title("M5Lite Flasher")
    root.geometry("600x400")

    # Detect devices
    devices = get_sd_devices()
    if not devices:
        messagebox.showerror("Error", "No /dev/sdX devices found. Please insert an SD card.")
        exit()

    # Device selection label and dropdown
    tk.Label(root, text="Select a storage device:", font=("Arial", 14)).pack(pady=10)

    device_frame = tk.Frame(root)
    device_frame.pack(pady=10, fill=tk.BOTH, expand=True)

    columns = ("Device", "Size", "Model")
    tree = ttk.Treeview(device_frame, columns=columns, show="headings")
    tree.heading("Device", text="Device")
    tree.heading("Size", text="Size")
    tree.heading("Model", text="Model")

    for device in devices:
        tree.insert("", tk.END, values=(device["device"], device["size"], device["model"]))

    tree.pack(fill=tk.BOTH, expand=True)

    # Progress bar
    progress_bar = ttk.Progressbar(root, orient="horizontal", length=400, mode="determinate")
    progress_bar.pack(pady=20)

    # Status label
    status_label = tk.Label(root, text="Waiting for user action...", font=("Arial", 12), fg="blue")
    status_label.pack(pady=10)

    # Flash button
    def start_flash():
        selected_item = tree.selection()
        if not selected_item:
            messagebox.showerror("Error", "Please select a valid device.")
            return

        selected_device = tree.item(selected_item, "values")
        device_dict = next((d for d in devices if d["device"] == selected_device[0]), None)
        if device_dict:
            flash_files(device_dict["device"], progress_bar, status_label)

    tk.Button(root, text="Flash OS", command=start_flash, font=("Arial", 12)).pack(pady=10)

    root.mainloop()

if __name__ == "__main__":
    main()
