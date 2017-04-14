/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 16:36:05 by dkovalch          #+#    #+#             */
/*   Updated: 2017/03/29 17:58:04 by dkovalch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSERT_H
# define ASSERT_H

# include <stdio.h>

/*
**If you have your own printf - comment this line, or it will use libc printf.
*/
# define PRINTMODE printf

/*
**if your usign your printf - write the name of your header here
*/

# ifndef PRINTMODE
#  include "ft_printf.h"
# endif

/*
**Usage:
**PRINT_MSG(msg)-prints the message you want(you can use all printf stuff here).
**PRINT_D_MSG(msg)-prints the message you want, only if DEBUG is defined
**(add "# define DEBUG" to you header to enable this).
**PRINT_MSG_D(msg)-alias for PRINT_D_MSG().
**ASSERT(assertion, msg)-if assertion is true - it prints the msg
**(u can use printf format here).
**
**Examples:
**
**PRINT_MSG("My var is %d, and this string is %s", i, str);
**PRINT_D_MSG("My var is %d, and this string is %s", i, str);
**PRINT_MSG_D("My var is %d, and this string is %s", i, str);
**
**ASSERT(1 == 1, "ONG! It is TRUE!!!");
**ASSERT_D(1 == 1, "Debug assert!");
*/

/*
**Change this to tweak the output by width.
*/

# define FILE_WIDTH "1"
# define LINE_WIDTH "3"
# define FUNC_WIDTH "15"

/*
**Change this to change colors.
*/

# define COLOR_INFO "\x1b[36m"
# define COLOR_MSG "\x1b[33m"
# define COLOR_ASRT "\x1b[31m"
# define COLOR_RESET "\x1b[0m"

/*
**Internal stuff - DONT TOUCH!:)
*/

# define ASSERT(assertion, ...)\
	{\
		if (assertion)\
		{\
			PRINT_MSG(COLOR_ASRT"assert"COLOR_RESET": ("COLOR_INFO #assertion COLOR_RESET") is "\
					  COLOR_ASRT"%s"COLOR_RESET" -> ", (assertion) ? "TRUE" : "FALSE");\
			PRINTMODE(COLOR_MSG); PRINTMODE(__VA_ARGS__); PRINTMODE("%s\n", COLOR_RESET);\
			fflush(stdout);\
		}\
	}

# define PRINT_MSG(...)\
	{\
		PRINTMODE("File "COLOR_INFO"%"FILE_WIDTH"s"COLOR_RESET, __FILE__);\
		PRINTMODE(" @ "COLOR_INFO"line %"LINE_WIDTH"d"COLOR_RESET, __LINE__);\
		PRINTMODE(" in "COLOR_INFO"%"FUNC_WIDTH"s"COLOR_RESET, __FUNCTION__);\
		PRINTMODE(" says: "COLOR_MSG);\
		PRINTMODE(__VA_ARGS__); PRINTMODE(COLOR_RESET); fflush(stdout);\
	}

# ifdef DEBUG
#  define ASSERT_D(assertion, ...) ASSERT(assertion, __VA_ARGS__)
#  define PRINT_MSG_D(...) PRINT_MSG(__VA_ARGS__)
#  define PRINT_D_MSG(...) PRINT_MSG(__VA_ARGS__)
# else
#  define ASSERT_D(assertion, ...)
#  define PRINT_MSG_D(...)
#  define PRINT_D_MSG(...)
# endif

#endif
