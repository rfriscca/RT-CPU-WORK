/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtdefs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/28 06:39:09 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/05 22:56:23 by vcaquant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTDEFS_H
# define RTDEFS_H

# define RANDOM				2
# define PROGRESSIVE		1
# define LEGACY				0

# define RAND_TRY			7

# define DEF_AMB			0.1
# define DEF_DIF			0.9
# define DEF_SPE			0.0

# define DEF_WIDTH			800
# define DEF_HEIGHT			600
# define DEF_AA				0
# define DEF_DEPH			2
# define DEF_REFLECT		0
# define DEF_REFRACT		0
# define DEF_FOV			70
# define DEF_PREVIEW		1
# define DEF_DISPLAY		LEGACY
# define DEF_3D_MODE		0
# define DEF_3D_OFFSET		0
# define DEF_3D_CONV		0
# define DEF_NAME			"3DTeam's Raytracer"
# define DEF_FOCUS			0
# define DEF_FOCUS_DST		5000
# define DEF_FOCUS_RANGE	3000
# define DEF_FOCUS_K		1.0
# define DEF_CAM_POSX		0.0
# define DEF_CAM_POSY		0.0
# define DEF_CAM_POSZ		0.0
# define DEF_CAM_ANGX		0.0
# define DEF_CAM_ANGY		0.0
# define DEF_CAM_ANGZ		0.0
# define DEF_CAM2_POSX		0.0
# define DEF_CAM2_POSY		0.0
# define DEF_CAM2_POSZ		0.0
# define DEF_CAM2_ANGX		0.0
# define DEF_CAM2_ANGY		0.0
# define DEF_CAM2_ANGZ		0.0
# define DEF_THREADS		4
# define MAX_THREADS		32

# define DEF_OBJ_POSX		0.0
# define MIN_OBJ_POSX		-99999.0
# define MAX_OBJ_POSX		99999.0
# define DEF_OBJ_POSY		0.0
# define MIN_OBJ_POSY		-99999.0
# define MAX_OBJ_POSY		99999.0
# define DEF_OBJ_POSZ		0.0
# define MIN_OBJ_POSZ		-99999.0
# define MAX_OBJ_POSZ		99999.0
# define DEF_OBJ_ANGX		0.0
# define DEF_OBJ_ANGY		0.0
# define DEF_OBJ_ANGZ		0.0
# define DEF_OBJ_EXPX		1.0
# define DEF_OBJ_EXPY		1.0
# define DEF_OBJ_EXPZ		1.0
# define DEF_COLOR			0xFF0000
# define DEF_COLOR2			0x00FF00
# define DEF_COLOR3			0x0000FF
# define DEF_COLOR_REFR		0xFFFFFF
# define DEF_SIZE			100.0
# define DEF_MOD			1.0
# define MIN_REFLECT_K		0.0
# define MAX_REFLECT_K		255.0
# define MIN_REFRACT_K		0.0
# define MAX_REFRACT_K		255.0
# define MIN_REFRACT_IND	1.0
# define MAX_REFRACT_IND	4.0
# define DEF_CAP1           0
# define DEF_CAP2           0

# define DEF_LIGHT_POSX		0.0
# define DEF_LIGHT_POSY		0.0
# define DEF_LIGHT_POSZ		0.0
# define DEF_LIGHT_ANGX		0.0
# define DEF_LIGHT_ANGY		0.0
# define DEF_LIGHT_ANGZ		0.0
# define DEF_LIGHT_K1		0.2
# define DEF_LIGHT_K2		1.0
# define DEF_LIGHT_K3		5.0
# define DEF_LIGHT_COLOR	0xFFFFFF
# define DEF_LIGHT_MOD		1.0

# define NONE				0
# define INTERLEAVED		1
# define SIDE_TO_SIDE		2

# define SPOT				1
# define GLOBAL				2

# define BUFF_NB			4
# define MIN_DEF_X			42
# define MIN_DEF_Y			42
# define MAX_DEF_X			2560
# define MAX_DEF_Y			1440

# define SPHERE				1
# define PLANE				2
# define DPLANE				4
# define CYLINDER			8
# define CONE				16
# define DISK				32
# define SQUARE				64
# define CUBE				128
# define PARABOLOID			256
# define GLASS				512

# define TTF_PATH			"./ressources/gui_font/"

#endif
