// components/Pulse/src/lexer.l

%{
#include "parser.hpp" // Include your parser header
%}

%%

"dropdown"      { return DROPDOWN; }
"slider"        { return SLIDER; }
"input"         { return INPUT; }
/* existing tokens */

%%
