/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   State.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/04/09 01:12:05 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace kdo
{
	typedef enum EStateFlags
	{
		clearbit	= 1 << -1,
		goodbit		= 1 << 0,
		eofbit		= 1 << 1,
		failbit 	= 1 << 2,
		badbit		= 1 << 3
	}	stateFlags;

	class State
	{
		protected:
			stateFlags	flags;

		public:
						State(stateFlags flags = failbit);
						State(State const &other);
						~State(void);
			bool		good(void) const;
			bool		eof(void) const;
			bool		fail(void) const;
			bool		bad(void) const;
			stateFlags	get(void) const;
			void		set(stateFlags flags);
			void		clear(void);
			bool		operator==(stateFlags flags) const;
			bool		operator!=(stateFlags flags) const;
			State		operator&(stateFlags flags) const;
			State		operator|(stateFlags flags) const;
			State		operator^(stateFlags flags) const;
			State const	&operator&=(stateFlags flags);
			State const	&operator|=(stateFlags flags);
			State const	&operator^=(stateFlags flags);
			bool		operator==(State const &other) const;
			bool		operator!=(State const &other) const;
			State		operator&(State const &other) const;
			State		operator|(State const &other) const;
			State		operator^(State const &other) const;
			State const	&operator&=(State const &other);
			State const	&operator|=(State const &other);
			State const	&operator^=(State const &other);
			State		operator~(void) const;
			State		&operator=(State const &other);
	};
}
