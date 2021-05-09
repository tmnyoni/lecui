//
// icon.h - icon widget interface
//
// lecui user interface library, part of the liblec library
// Copyright (c) 2019 Alec Musasa (alecmus at live dot com)
//
// Released under the CC-BY-NC 2.0 license. For full details see the file
// LICENSE.txt or go to https://github.com/alecmus/liblec/blob/master/LICENSE.md
//

#pragma once

#if defined(LECUI_EXPORTS)
#include "widget.h"
#else
#include <liblec/lecui/widgets/widget.h>
#endif

namespace liblec {
	namespace lecui {
		namespace widgets {
			/// <summary>Icon widget.</summary>
			class lecui_api icon {
			public:
				/// <summary>Icon widget specifications.</summary>
				/// <remarks>Recommended size with defaults is 180x78px.</remarks>
				class icon_specs : public specs {
				public:
					icon_specs() {
						rect.size({ 180.f, 78.f });
						font_size = 11.f;
					};

					/// <summary>Text position in icon.</summary>
					enum class icon_text_position {
						right,
						left,
						top,
						bottom,
					};

					/// <summary>The maximum size of the image square's side.</summary>
					/// <remarks>Set to 0.f for unlimited image size.</remarks>
					float max_image_size = 48.f;

					/// <summary>The thickness of the border.</summary>
					float border = .5f;

					/// <summary>The color of the border.</summary>
					color color_border;

					/// <summary>The color of the descriptive text.</summary>
					color color_text_description;

					/// <summary>The size of the descriptive text.</summary>
					float font_size_description = 8.5f;

					/// <summary>The horizontal radius of the corners.</summary>
					float corner_radius_x = 3.f;

					/// <summary>The vertical radius of the corners.</summary>
					float corner_radius_y = 3.f;

					/// <summary>ID of PNG resource containing the image.</summary>
					/// <remarks>PNG resource takes precedence over image file.</remarks>
					int png_resource = 0;

					/// <summary>Full path to image file.</summary>
					/// <remarks>PNG resource takes precedence over image file.</remarks>
					std::string file;

					/// <summary>The quality of the image in the icon.</summary>
					image_quality quality = image_quality::high;

					/// <summary>Descriptive text placed under the icon text.</summary>
					std::string description;

					/// <summary>The position of the text.</summary>
					icon_text_position text_position = icon_text_position::right;

					bool operator==(const icon_specs&);
					bool operator!=(const icon_specs&);
				};

				/// <summary>Icon constructor.</summary>
				/// <param name="page">The container to place it in.</param>
				/// <remarks>This constructs the widget with an internally generated random
				/// alias.</remarks>
				icon(containers::page& page);

				/// <summary>Icon constructor.</summary>
				/// <param name="page">The container to place it in.</param>
				/// <param name="alias">The in-page unique alias, e.g. "users".</param>
				icon(containers::page& page, const std::string& alias);
				~icon();

				/// <summary>Get the icon specifications.</summary>
				/// <returns>A reference to the icon specifications.</returns>
				[[nodiscard]]
				icon_specs& specs();

				/// <summary>Get the icon specifications.</summary>
				/// <returns>A reference to the icon specifications.</returns>
				/// <remarks>Alternative to specs() for more terse code.</remarks>
				[[nodiscard]]
				icon_specs& operator()();

				/// <summary>Get the specifications of a icon.</summary>
				/// <param name="fm">The form containing the icon.</param>
				/// <param name="path">The full path to the widget, e.g.
				/// "sample_page/sample_pane/users".</param>
				/// <returns>A reference to the icon specifications.</returns>
				/// <remarks>Throws on failure.</remarks>
				[[nodiscard]]
				static icon_specs& specs(form& fm, const std::string& path);

			private:
				class impl;
				impl& d_;

				// Default constructor and copying an object of this class are not allowed
				icon() = delete;
				icon(const icon&) = delete;
				icon& operator=(const icon&) = delete;
			};
		}
	}
}
