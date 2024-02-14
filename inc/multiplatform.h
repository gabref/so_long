/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplatform.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:24:48 by galves-f          #+#    #+#             */
/*   Updated: 2024/02/14 11:28:09 by galves-f         ###   ########.fr       */
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
#  define DESTROY_NOTIFY DestroyNotify
#  define STRUCT_NOTIFY_MASK StructureNotifyMask

/* keys definitions */
#  define KEY_ESCAPE XK_Escape

# elif __APPLE__

#  include "../libs/mlx_mac/mlx.h"
#  include <X11/X.h>
#  define KEY_RELEASE 3
#  define KEY_RELEASE_MASK 1L << 1
#  define DESTROY_NOTIFY 17
#  define STRUCT_NOTIFY_MASK 1L << 17

#  define KEY_ESCAPE 53

# endif

#endif
