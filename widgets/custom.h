//
// custom.h - custom widget interface
//
// lecui user interface library, part of the liblec library
// Copyright (c) 2019 Alec Musasa (alecmus at live dot com)
//
// Released under the MIT license. For full details see the
// file LICENSE.txt
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
			/// <summary>Custom widget. To instantiate and add to a container use the <see cref="add"></see> static method.</summary>
			class lecui_api custom : public widget, public badge_widget {
			public:
				/// <summary>
				/// Handler for resource creation. The pointers need to be cast back to their
				/// Direct2D equivalents on the client side before they can be used. e.g.
				/// _ID2D1HwndRenderTarget can be cast using reinterpret_cast to a
				/// ID2D1HwndRenderTarget. This will be called internally by the library when
				/// device-specific resources associated with the Direct3D device need to be
				/// (re)created.
				/// </summary>
				std::function<void(
					void* _ID2D1HwndRenderTarget,
					void* _IDWriteFactory,
					void* _IWICImagingFactory)>
					on_create_resources = nullptr;

				/// <summary>
				/// Handler for discarding resources. This handler will be called internally
				/// by the library if the Direct3D device dissapears.
				/// </summary>
				std::function<void()> on_discard_resources = nullptr;

				/// <summary>
				/// Handler for rendering. All drawing should be done here. Information about
				/// the widget status are provided through the parameters, e.g. _selected is
				/// true if the widget is currently selected in the user interface and
				/// _pressed is true if the left mouse button has not yet been released after
				/// it was pressed down while the cursor was within the widget.
				/// </summary>
				std::function<void(
					void* _D2D1_RECT_F,
					bool _enabled,
					bool _hit,
					bool _pressed,
					bool _selected)>
					on_render = nullptr;

				/// <summary>Check whether widget specs are equal. Only those properties that
				/// require the widget resources to be re-created are considered.</summary>
				/// <param name="param">The specs to compare to.</param>
				/// <returns>Returns true if the specs are equal, else false.</returns>
				bool operator==(const custom& param);

				/// <summary>Check whether widget specs are NOT equal. Only those properties that
				/// require the widget resources to be re-created are considered.</summary>
				/// <param name="param">The specs to compare to.</param>
				/// <returns>Returns true if the specs are NOT equal, else false.</returns>
				bool operator!=(const custom& param);

				// generic widget

				/// <summary>Get or set the widget text.</summary>
				/// <returns>A reference to the widget text.</returns>
				std::string& text() override;

				/// <summary>Set the widget's text.</summary>
				/// <param name="text">The text.</param>
				/// <returns>A reference to the modified object.</returns>
				custom& text(const std::string& text);

				/// <summary>Get or set the widget's tooltip text.</summary>
				/// <returns>A reference to the tooltip text.</returns>
				std::string& tooltip() override;

				/// <summary>Set the tooltip text.</summary>
				/// <param name="tooltip">The tooltip text.</param>
				/// <returns>A reference to the modified object.</returns>
				custom& tooltip(const std::string& tooltip);

				/// <summary>Get or set the badge specs.</summary>
				/// <returns>A reference to the badge specs.</returns>
				badge_specs& badge() override;

				/// <summary>Set the badge specs.</summary>
				/// <param name="badge">The badge specs.</param>
				/// <returns>A reference to the modified object.</returns>
				custom& badge(const badge_specs& badge);

				/// <summary>Get or set the position and dimensions of the widget.</summary>
				/// <returns>A reference to the widget rectangle.</returns>
				/// <remarks>The position is in reference to the widget's container.</remarks>
				lecui::rect& rect() override;

				/// <summary>Set the position and dimensions of the widget.</summary>
				/// <param name="rect">The widget's rectangle.</param>
				/// <returns>A reference to the modified object.</returns>
				custom& rect(const lecui::rect& rect);

				/// <summary>Get or set the behaviour of the widget when its container is resized.</summary>
				/// <returns>A reference to the resize parameters as defined in <see cref="resize_params"></see>.</returns>
				resize_params& on_resize() override;

				/// <summary>Set the behaviour of the widget when its container is resized.</summary>
				/// <param name="on_resize">The resize parameters as defined in <see cref="resize_params"></see>.</param>
				/// <returns>A reference to the modified object.</returns>
				custom& on_resize(const resize_params& on_resize);

				/// <summary>Get or set the mouse cursor to use then over the widget.</summary>
				/// <returns>A reference to the cursor type as defined in <see cref="cursor_type"></see>.</returns>
				cursor_type& cursor() override;

				/// <summary>Set the mouse cursor to use when over the widget.</summary>
				/// <param name="cursor">The cursor type as defined in <see cref="cursor_type"></see>.</param>
				/// <returns>A reference to the modified object.</returns>
				custom& cursor(const cursor_type cursor);

				/// <summary>Get or set the default widget font, e.g. "Georgia".</summary>
				/// <returns>A reference to the widget's font name.</returns>
				std::string& font() override;

				/// <summary>Set the default widget font.</summary>
				/// <param name="font">The font's name, e.g. "Georgia".</param>
				/// <returns>A reference to the modified object.</returns>
				custom& font(const std::string& font);

				/// <summary>Get or set the default widget font size in points, e.g. 9.0f.</summary>
				/// <returns>A reference to the widget's font size.</returns>
				float& font_size() override;

				/// <summary>Set the widget's font size.</summary>
				/// <param name="font_size">The font size in points, e.g. 9.0f.</param>
				/// <returns>A reference to the modified object.</returns>
				custom& font_size(const float& font_size);

				/// <summary>Get or set the color of the widget's text.</summary>
				/// <returns>A reference to the widget's text color.</returns>
				color& color_text() override;

				/// <summary>Set the color of the widget's text.</summary>
				/// <param name="color_text">The color of the widget's text.</param>
				/// <returns>A reference to the modified object.</returns>
				custom& color_text(const color& color_text);

				/// <summary>Get or set the fill color of the widget.</summary>
				/// <returns>A reference to the widget's fill color.</returns>
				color& color_fill() override;

				/// <summary>Set the fill color of the widget.</summary>
				/// <param name="color_fill">The fill color.</param>
				/// <returns>A reference to the modified object.</returns>
				custom& color_fill(const color& color_fill);

				/// <summary>Get or set the widget's color when the mouse is hovered over it.</summary>
				/// <returns>A reference to the widget's hover color.</returns>
				color& color_hot() override;

				/// <summary>Set the widget's color when the mouse is hovered over it.</summary>
				/// <param name="color_hot">The color.</param>
				/// <returns>A reference to the modified object.</returns>
				custom& color_hot(const color& color_hot);

				/// <summary>Get or set the widget's color when selected.</summary>
				/// <returns>A reference to the widget's color when selected.</returns>
				color& color_selected() override;

				/// <summary>Set the widget's color when selected.</summary>
				/// <param name="color_selected">The widget's color when selected.</param>
				/// <returns>A reference to the modified object.</returns>
				custom& color_selected(const color& color_selected);

				/// <summary>Get or set the widget's color when it is disabled.</summary>
				/// <returns>a reference to the property.</returns>
				color& color_disabled() override;

				/// <summary>Set the widget's color when it is disabled.</summary>
				/// <param name="color_disabled">The color of the widget when it is disabled, as defined in <see cref='color'></see>.</param>
				/// <returns>A reference to the modified object.</returns>
				custom& color_disabled(const color& color_disabled);

			public:
				/// <summary>Add a custom widget to a container.</summary>
				/// <param name="page">The container to place the widget in.</param>
				/// <param name="alias">The in-page unique alias, e.g. "diagram".</param>
				/// <returns>A reference to the widget specifications.</returns>
				/// <remarks>If an empty alias is given an internally generated random
				/// alias will be assigned.</remarks>
				[[nodiscard]]
				static custom& add(containers::page& page, const std::string& alias = std::string());

				/// <summary>Get the specifications of a custom widget.</summary>
				/// <param name="fm">A reference to the form.</param>
				/// <param name="path">The full path to the widget, e.g. "sample_page/right_pane/tab_pane/tab_two/diagram".</param>
				/// <returns>A reference to the widget specifications.</returns>
				/// <remarks>Throws on failure. For faster coding and more readable code consider
				/// calling this static method through the helper macro provided.</remarks>
				[[nodiscard]]
				static custom& get(form& fm, const std::string& path);
			};
		}
	}
}

#if defined(lecui_helper)
/// Helper for getting custom widget. 'Get' method documentation applies.
#define get_custom(path) liblec::lecui::widgets::custom::get(*this, path)
#endif
