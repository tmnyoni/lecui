//
// image_view.h - image view widget interface
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
			/// <summary>Image view widget specifications.</summary>
			/// <remarks>Default size is 200x200px.</remarks>
			class lecui_api image_view_specs : public specs {
				float _border = .5f;
				color _color_border;
				float _corner_radius_x = .0f;
				float _corner_radius_y = .0f;
				int _png_resource = 0;
				std::string _file;
				image_quality _quality = image_quality::medium;
				bool _enlarge_if_smaller = false;
				bool _keep_aspect_ratio = true;

			public:
				image_view_specs() {
					_cursor = cursor_type::hand;
					_rect.size({ 200.f, 200.f });
				}

				bool operator==(const image_view_specs&);
				bool operator!=(const image_view_specs&);

				// generic specs

				std::string& text() override;
				image_view_specs& text(const std::string& text);

				std::string& tooltip() override;
				image_view_specs& tooltip(const std::string& tooltip);

				lecui::rect& rect() override;
				image_view_specs& rect(const lecui::rect& rect);

				resize_params& on_resize() override;
				image_view_specs& on_resize(const resize_params& on_resize);

				cursor_type& cursor() override;
				image_view_specs& cursor(const cursor_type cursor);

				std::string& font() override;
				image_view_specs& font(const std::string& font);

				float& font_size() override;
				image_view_specs& font_size(const float& font_size);

				color& color_text() override;
				image_view_specs& color_text(const color& color_text);

				color& color_fill() override;
				image_view_specs& color_fill(const color& color_fill);

				color& color_hot() override;
				image_view_specs& color_hot(const color& color_hot);

				color& color_selected() override;
				image_view_specs& color_selected(const color& color_selected);

				color& color_disabled() override;
				image_view_specs& color_disabled(const color& color_disabled);

				// widget specific specs

				/// <summary>Get or set the thickness of the border.</summary>
				/// <returns>A reference to the border thickness, in pixels.</returns>
				float& border();

				/// <summary>Set the thickness of the border.</summary>
				/// <param name="border">The border thickness, in pixels.</param>
				/// <returns>A reference to the modified object.</returns>
				image_view_specs& border(const float& border);

				/// <summary>Get or set the color of the border.</summary>
				/// <returns>A reference to the border color, as defined in <see cref="color"></see>.</returns>
				color& color_border();

				/// <summary>Set the color of the border.</summary>
				/// <param name="color_border">The border color, as defined in <see cref="color"></see>.</param>
				/// <returns>A reference to the modified object.</returns>
				image_view_specs& color_border(const color& color_border);

				/// <summary>Get or set the horizontal radius of the corners.</summary>
				/// <returns>A reference to the radius, in pixels.</returns>
				float& corner_radius_x();

				/// <summary>Set the horizontal radius of the corners.</summary>
				/// <param name="corner_radius_x">The horizontal radius of the corner, in pixels.</param>
				/// <returns>A reference to the modified object.</returns>
				image_view_specs& corner_radius_x(const float& corner_radius_x);

				/// <summary>Get or set the vertical radius of the corners.</summary>
				/// <returns>A reference to the radius, in pixels.</returns>
				float& corner_radius_y();

				/// <summary>Set the vertical radius of the corners.</summary>
				/// <param name="corner_radius_y">The horizontal radius of the corner, in pixels.</param>
				/// <returns>A reference to the modified object.</returns>
				image_view_specs& corner_radius_y(const float& corner_radius_y);

				/// <summary>Get or set the icon's PNG resource.</summary>
				/// <returns>A reference to the resource's ID.</returns>
				/// <remarks>PNG resource takes precedence over image file.</remarks>
				int& png_resource();

				/// <summary>Set the icon's PNG resource.</summary>
				/// <param name="png_resource">The ID of PNG resource.</param>
				/// <returns>A reference to the modified object.</returns>
				/// <remarks>PNG resource takes precedence over image file.</remarks>
				image_view_specs& png_resource(const int& png_resource);

				/// <summary>Get or set the path to the icon's image file.</summary>
				/// <returns>A reference to the path.<returns>
				/// <remarks>PNG resource takes precedence over image file.</remarks>
				std::string& file();

				/// <summary>Set the path to the icon's image file.</summary>
				/// <param name="file">The path to the file.</param>
				/// <returns>A reference to the modified object.</returns>
				/// <remarks>PNG resource takes precedence over image file.</remarks>
				image_view_specs& file(const std::string& file);

				/// <summary>Get or set the quality of the image in the icon.</summary>
				/// <returns>A reference to the quality property.</returns>
				/// <remarks>Lower quality means greater performance and vice-versa.</remarks>
				image_quality& quality();

				/// <summary>Set the quality of the image in the icon.</summary>
				/// <param name="quality">The quality of the image, as defined in <see cref="image_quality"></see>.</param>
				/// <returns>A reference to the modified object.</returns>
				/// <remarks>Lower quality means greater performance and vice-versa.</remarks>
				image_view_specs& quality(const image_quality& quality);

				/// <summary>Get or set the property for enlarging the image to fill up the rect if the image
				/// is smaller than the rectangle.</summary>
				/// <returns>A reference to the property.</returns>
				bool& enlarge_if_smaller();

				/// <summary>Set the property for enlarging the image to fill up the rect if the image
				/// is smaller than the rectangle.</summary>
				/// <param name="enlarge_if_smaller">Whether to enlarge the image to fill up the rect if the
				/// image is smaller than the rectangle.</param>
				/// <returns>A reference to the modified object.</returns>
				image_view_specs& enlarge_if_smaller(const bool& enlarge_if_smaller);

				/// <summary>Get or set the property for whether to keep the image aspect ratio.</summary>
				/// <returns>A reference to the property.</returns>
				bool& keep_aspect_ratio();

				/// <summary>Set the property for whether to keep the image aspect ratio.</summary>
				/// <param name="keep_aspect_ratio">Whether to keep the image aspect ratio.</param>
				/// <returns>A reference to the modified object.</returns>
				image_view_specs& keep_aspect_ratio(const bool& keep_aspect_ratio);
			};

			/// <summary>Image view widget builder.</summary>
			class lecui_api image_view_builder {
			public:
				/// <summary>Image view builder constructor.</summary>
				/// <param name="page">The container to place the widget in.</param>
				/// <remarks>This constructs the widget with an internally generated random
				/// alias.</remarks>
				image_view_builder(containers::page& page);

				/// <summary>Image view builder constructor.</summary>
				/// <param name="page">The container to place the widget in.</param>
				/// <param name="alias">The in-page unique alias, e.g. "avatar".</param>
				image_view_builder(containers::page& page, const std::string& alias);
				~image_view_builder();

				/// <summary>Get the specifications of the image view.</summary>
				/// <returns>A reference to the image view specifications.</returns>
				[[nodiscard]]
				image_view_specs& specs();

				/// <summary>Get the specifications of the image view.</summary>
				/// <returns>A reference to the image view specifications.</returns>
				/// <remarks>Alternative to specs() for more terse code.</remarks>
				[[nodiscard]]
				image_view_specs& operator()();

				/// <summary>Get the specifications of an image.</summary>
				/// <param name="fm">The form containing the image.</param>
				/// <param name="path">The full path to the widget, e.g.
				/// "sample_page/sample_tab_pane/tab_three/pane_two/avatar".</param>
				/// <returns>A reference to the image specifications.</returns>
				/// <remarks>Throws on failure.</remarks>
				[[nodiscard]]
				static image_view_specs& specs(form& fm, const std::string& path);

			private:
				class impl;
				impl& _d;

				// Default constructor and copying an object of this class are not allowed
				image_view_builder() = delete;
				image_view_builder(const image_view_builder&) = delete;
				image_view_builder& operator=(const image_view_builder&) = delete;
			};
		}
	}
}
