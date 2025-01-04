#!/usr/bin/env python3
import os
import sys
import subprocess
import threading
import tkinter as tk
from tkinter import ttk, messagebox
import pyudev
import psutil
import re

class InstallOSApp:
    def __init__(self, master):
        self.master = master
        master.title("Custom OS Installer")
        master.geometry("700x500")
        master.resizable(False, False)

        self.style = ttk.Style()
        self.style.theme_use('clam')

        # Instruction Label
        self.label = ttk.Label(master, text="Select the storage device to install the OS:", font=("Helvetica", 12))
        self.label.pack(pady=10)

        # Treeview for device listing
        columns = ("Device", "Model", "Size", "Mountpoint")
        self.tree = ttk.Treeview(master, columns=columns, show='headings', selectmode='browse')
        for col in columns:
            self.tree.heading(col, text=col)
            self.tree.column(col, width=150, anchor='center')
        self.tree.pack(pady=10, fill=tk.BOTH, expand=True)

        # Scrollbar for Treeview
        self.scrollbar = ttk.Scrollbar(master, orient="vertical", command=self.tree.yview)
        self.tree.configure(yscroll=self.scrollbar.set)
        self.scrollbar.pack(side='right', fill='y')

        # Install Button
        self.install_button = ttk.Button(master, text="Install OS", command=self.install_os)
        self.install_button.pack(pady=20)

        # Progress Bar
        self.progress = ttk.Progressbar(master, orient='horizontal', mode='determinate', length=600)
        self.progress.pack(pady=10)

        # Status Label
        self.status_label = ttk.Label(master, text="", font=("Helvetica", 10))
        self.status_label.pack()

        # Load devices
        self.load_devices()

    def load_devices(self):
        """Detect and list removable storage devices."""
        context = pyudev.Context()
        self.devices = []

        for device in context.list_devices(subsystem='block', DEVTYPE='partition'):
            try:
                parent = device.find_parent('block', 'disk')
                if parent and parent.attributes.asbool('removable'):
                    device_node = device.device_node
                    if device_node and 'loop' not in device_node:
                        mountpoint = self.get_mountpoint(device_node)
                        size = self.get_device_size(device_node)
                        model = parent.get('ID_MODEL', 'Unknown')
                        self.devices.append({
                            'device': device_node,
                            'model': model,
                            'size': size,
                            'mountpoint': mountpoint
                        })
            except AttributeError:
                continue

        # Populate Treeview
        for dev in self.devices:
            self.tree.insert('', tk.END, values=(dev['device'], dev['model'], dev['size'], dev['mountpoint']))

        if not self.devices:
            messagebox.showinfo("No Devices Found", "No removable storage devices were detected. Please insert a device and restart the application.")
            self.install_button.config(state='disabled')

    def get_mountpoint(self, device_node):
        """Retrieve the mount point of the device."""
        partitions = psutil.disk_partitions(all=False)
        for partition in partitions:
            if partition.device == device_node:
                return partition.mountpoint
        return "Not Mounted"

    def get_device_size(self, device_node):
        """Get the size of the device in GB."""
        try:
            with open(f'/sys/block/{os.path.basename(device_node)}/size', 'r') as f:
                sectors = int(f.read().strip())
                size_gb = round(sectors * 512 / (1024**3), 2)  # Assuming 512 bytes per sector
                return f"{size_gb} GB"
        except:
            return "Unknown"

    def install_os(self):
        """Initiate the OS installation process."""
        selected = self.tree.selection()
        if not selected:
            messagebox.showwarning("No Selection", "Please select a storage device to proceed.")
            return

        device_info = self.tree.item(selected)['values']
        device = device_info[0]
        model = device_info[1]
        size = device_info[2]
        mountpoint = device_info[3]

        if mountpoint == "Not Mounted":
            mount_confirm = messagebox.askyesno("Mount Device", f"The device {device} is not mounted. Would you like to mount it now?")
            if mount_confirm:
                if not self.mount_device(device):
                    return
            else:
                return

        # Confirm Installation
        confirm = messagebox.askyesno("Confirm Installation",
                                      f"Are you sure you want to install the OS on {device}?\n"
                                      "This will erase all existing data on the selected device.")
        if not confirm:
            return

        # Check if 'components' directory exists
        if not os.path.exists('components'):
            messagebox.showerror("Missing Components", "The 'components' directory was not found. Please ensure it exists and contains the OS files.")
            return

        # Start Installation in a Separate Thread
        threading.Thread(target=self.run_installation, args=(device, mountpoint), daemon=True).start()

    def mount_device(self, device_node):
        """Mount the device using udisksctl."""
        try:
            result = subprocess.check_output(['udisksctl', 'mount', '-b', device_node], stderr=subprocess.STDOUT)
            mount_point = result.decode().strip().split()[-1].rstrip('.')
            self.update_status(f"Mounted {device_node} at {mount_point}")
            # Update Treeview
            for dev in self.devices:
                if dev['device'] == device_node:
                    dev['mountpoint'] = mount_point
                    self.tree.set(self.tree.selection(), column="Mountpoint", value=mount_point)
                    break
            return True
        except subprocess.CalledProcessError as e:
            messagebox.showerror("Mount Error", f"Failed to mount {device_node}.\nError: {e.output.decode()}")
            return False

    def run_installation(self, device_node, mountpoint):
        """Perform the installation steps."""
        # Format the Device (Erase All Data)
        format_confirm = messagebox.askyesno("Format Device",
                                             f"Do you want to erase all data on {device_node} before installation?")
        if format_confirm:
            self.update_status(f"Formatting {device_node}...")
            if not self.format_device(device_node):
                self.update_status("Formatting failed.")
                return

        # Copy Files Using rsync
        self.update_status("Starting file copy...")
        rsync_command = ['rsync', '-a', '--info=progress2', 'components/', mountpoint + '/']

        process = subprocess.Popen(rsync_command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)

        total_size = self.get_total_size('components')
        copied_size = 0

        # Regular expression to parse rsync progress
        progress_regex = re.compile(r'(\d+)%')

        for line in process.stdout:
            match = progress_regex.search(line)
            if match:
                percent = int(match.group(1))
                self.update_progress(percent)
                self.update_status(f"Copying files... {percent}% completed.")
            else:
                self.update_status(line.strip())

        process.wait()

        if process.returncode != 0:
            messagebox.showerror("Installation Error", "An error occurred during the installation process.")
            self.update_status("Installation failed.")
            return

        self.update_progress(100)
        self.update_status("Installation completed successfully.")

        # Eject the Device
        eject_confirm = messagebox.askyesno("Eject Device", "Do you want to eject the device now?")
        if eject_confirm:
            self.eject_device(device_node)

    def format_device(self, device_node):
        """Format the device with FAT32 filesystem."""
        try:
            # Unmount if mounted
            mountpoint = self.get_mountpoint(device_node)
            if mountpoint != "Not Mounted":
                self.unmount_device(device_node)

            # Format using mkfs.vfat
            subprocess.check_output(['sudo', 'mkfs.vfat', '-F', '32', device_node], stderr=subprocess.STDOUT)
            self.update_status(f"Formatted {device_node} successfully.")
            return True
        except subprocess.CalledProcessError as e:
            messagebox.showerror("Format Error", f"Failed to format {device_node}.\nError: {e.output.decode()}")
            return False

    def unmount_device(self, device_node):
        """Unmount the device using udisksctl."""
        try:
            subprocess.check_output(['udisksctl', 'unmount', '-b', device_node], stderr=subprocess.STDOUT)
            self.update_status(f"Unmounted {device_node}.")
            return True
        except subprocess.CalledProcessError as e:
            messagebox.showerror("Unmount Error", f"Failed to unmount {device_node}.\nError: {e.output.decode()}")
            return False

    def eject_device(self, device_node):
        """Eject the device using udisksctl."""
        try:
            subprocess.check_output(['udisksctl', 'power-off', '-b', device_node], stderr=subprocess.STDOUT)
            self.update_status(f"Ejected {device_node} successfully.")
            messagebox.showinfo("Ejected", f"{device_node} has been safely ejected.")
        except subprocess.CalledProcessError as e:
            messagebox.showerror("Eject Error", f"Failed to eject {device_node}.\nError: {e.output.decode()}")

    def get_total_size(self, directory):
        """Calculate the total size of the source directory."""
        total = 0
        for dirpath, dirnames, filenames in os.walk(directory):
            for f in filenames:
                fp = os.path.join(dirpath, f)
                if os.path.exists(fp):
                    total += os.path.getsize(fp)
        return total

    def update_progress(self, percent):
        """Update the progress bar."""
        self.progress['value'] = percent
        self.master.update_idletasks()

    def update_status(self, message):
        """Update the status label."""
        self.status_label.config(text=message)
        self.master.update_idletasks()

def main():
    root = tk.Tk()
    app = InstallOSApp(root)
    root.mainloop()

if __name__ == "__main__":
    if os.geteuid() == 0:
        print("Please run this installer as a regular user, not as root.")
        sys.exit(1)
    main()
