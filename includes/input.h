/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:38:50 by adavitas          #+#    #+#             */
/*   Updated: 2026/02/25 17:38:52 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# ifndef INPUT_H
# define INPUT_H

/* ── Keyboard keycodes (X11 / Linux) ───────────────────────── */
# define KEY_ESC		65307
# define KEY_W			'w'
# define KEY_A			'a'
# define KEY_S			's'
# define KEY_D			'd'
# define KEY_LEFT		65361
# define KEY_RIGHT		65363
# define KEY_UP			65362
# define KEY_DOWN		65364

/* ── MLX hook event IDs ─────────────────────────────────────── */
# define ON_KEYPRESS	2
# define ON_CLOSE		17

/* ── MLX hook event masks ───────────────────────────────────── */
# define KEYPRESS_MASK	1L
# define CLOSE_MASK		131072L

#endif
