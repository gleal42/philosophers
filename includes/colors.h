#ifndef COLORS_H
# define COLORS_H

# define RED	"\e[0;31m"
# define GRN	"\e[0;32m"
# define BLU   "\e[0;34m"
# define MAG   "\e[0;35m"
# define CYN   "\e[0;36m"
# define LRED	"\e[1;31m"
# define LGRN	"\e[1;32m"
# define YEL   "\e[1;33m"
# define LBLU   "\e[1;34m"
# define LMAG   "\e[1;35m"
# define LCYN   "\e[1;36m"
# define RESET_COLOR "\e[m"


typedef enum c_colors{
red,
grn,
blu, 
mag, 
cyn, 
lred,
lgrn,
yel,
lblu,
lmag,
lcyn,
} colors;

#endif
