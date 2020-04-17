/*
** button.h - button widget interface
**
** lecui user interface library
** Copyright (c) 2019 Alec T. Musasa (alecmus at live dot com)
**
*******************************************************************************
** This file is part of the liblec library which is released under the Creative
** Commons Attribution Non-Commercial 2.0 license (CC-BY-NC 2.0). See the file
** LICENSE.txt or go to https://github.com/alecmus/liblec/blob/master/LICENSE.md
** for full license details.
*/

#pragma once

#if defined(LECUI_EXPORTS)
	#include "widget.h"
#else
	#include <liblec/lecui/widgets/widget.h>
#endif

namespace liblec {
	namespace lecui {
		namespace widgets {
			/// <summary>Button widget.</summary>
			class lecui_api button {
			public:
				/// <summary>Button widget specifications.</summary>
				/// <remarks>Recommended size with defaults is 80x25px.</remarks>
				class button_specs : public specs {
				public:
					button_specs() {
						rect.size({ 80.f, 25.f });
						color_text = { 0, 0, 0, 255 };
						color_fill = { 229, 229, 229, 255 };
						color_hot = { 240, 240, 240, 255 };
						color_selected = { 0, 120, 170, 100 };
					}
					float border = .5f;
					float corner_radius_x = 5.f;
					float corner_radius_y = 5.f;
					color color_border = { 150, 150, 150, 255 };

					bool operator==(const button_specs&);
					bool operator!=(const button_specs&);
				};

				/// <summary>Button constructor.</summary>
				/// <param name="page">The container to place it in.</param>
				/// <param name="alias">The in-page unique alias, e.g. "next_button".</param>
				button(containers::page& page, const std::string& alias);
				~button();

				/// <summary>Get the button specifications.</summary>
				/// <returns>A reference to the button specifications.</returns>
				[[nodiscard]]
				button_specs& specs();

				/// <summary>Get the button specifications.</summary>
				/// <returns>A reference to the button specifications.</returns>
				/// <remarks>Alternative to specs() for more terse code.</remarks>
				[[nodiscard]]
				button_specs& operator()();

				/// <summary>Get the specifications of a button.</summary>
				/// <param name="fm">The form containing the button.</param>
				/// <param name="path">The full path to the widget, e.g.
				/// "sample_page/sample_pane/next_button".</param>
				/// <returns>A reference to the button specifications.</returns>
				/// <remarks>Throws on failure.</remarks>
				[[nodiscard]]
				static button_specs& specs(form& fm, const std::string& path);

			private:
				class impl;
				impl& d_;

				// Default constructor and copying an object of this class are not allowed
				button();
				button(const button&);
				button& operator=(const button&);
			};
		}
	}
}
