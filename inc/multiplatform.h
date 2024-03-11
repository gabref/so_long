/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplatform.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:24:48 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/10 23:24:04 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTIPLATFORM_H
# define MULTIPLATFORM_H

# ifdef __linux__

#  include "../libs/mlx_linux/mlx.h"
#  include <X11/X.h>
#  include <X11/keysym.h>

#  define KEY_RELEASE KeyRelease
#  define KEY_RELEASE_MASK KeyReleaseMask
#  define KEY_PRESS KeyPress
#  define KEY_PRESS_MASK KeyPressMask
#  define DESTROY_NOTIFY DestroyNotify
#  define STRUCT_NOTIFY_MASK StructureNotifyMask

/* keys definitions */
#  define KEY_ESCAPE XK_Escape
#  define KEY_UP XK_Up
#  define KEY_DOWN XK_Down
#  define KEY_LEFT XK_Left
#  define KEY_RIGHT XK_Right
#  define KEY_W XK_w
#  define KEY_A XK_a
#  define KEY_S XK_s
#  define KEY_D XK_d
# define KEY_SPACE XK_space

#  define destroy_window(w) destroy_window_linux(w)

# elif __APPLE__

#  include "../libs/mlx_mac/mlx.h"
#  define KEY_RELEASE 3
#  define KEY_RELEASE_MASK 1L << 1
#  define KEY_PRESS 2
#  define KEY_PRESS_MASK 1L << 0
#  define DESTROY_NOTIFY 17
#  define STRUCT_NOTIFY_MASK 1L << 17

#  define KEY_ESCAPE 53
#  define KEY_UP 126
#  define KEY_DOWN 125
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_SPACE 49

#  define destroy_window(w) destroy_window_mac(w)

# endif

#endif
