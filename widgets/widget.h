//
// widget.h - widget interface
//
// lecui user interface library, part of the liblec library
// Copyright (c) 2019 Alec Musasa (alecmus at live dot com)
//
// Released under the CC-BY-NC 2.0 license. For full details see the file
// LICENSE.txt or go to https://github.com/alecmus/liblec/blob/master/LICENSE.md
//

#pragma once

#if defined(LECUI_EXPORTS)
#include "../form.h"
#include "../containers/page.h"
#else
#include <liblec/lecui/form.h>
#endif

namespace liblec {
	namespace lecui {
		namespace widgets {
			/// <summary>Base class for all widget specifications.</summary>
			class lecui_api specs {
			public:
				/// <summary>Resize parameters.</summary>
				/// <remarks>Affects how the widget behaves when the immediate container's
				/// dimensions change.</remarks>
				struct resize_params {
					/// <summary>The percentage rate for following the container's right border.
					/// 0 = doesn't move horizontally, 100 = moves same number of pixels
					/// horizontally that the container's right border has moved.
					/// </summary>
					float perc_x = 0.f;

					/// <summary>The percentage rate for following the container's bottom border.
					/// 0 = doesn't move vertically, 100 = moves same number of pixels vertically
					/// that the container's bottom border has moved.</summary>
					float perc_y = 0.f;

					/// <summary>The percentage rate for following the container's change in width.
					/// 0 = doesn't follow change in container's width, 100 = width changes at 
					/// same rate as that of container.</summary>
					float perc_width = 0.f;

					/// <summary>The percentage rate for following the container's change in 
					/// height. 0 = doesn't follow change in container's height, 100 = height 
					/// changes at same rate as that of container.</summary>
					float perc_height = 0.f;

					/// Minimum coordinates permitted as widget moves
					float min_x = 0.f;
					float min_y = 0.f;

					/// Maximum coordinates permitted as widget moves
					float max_x = 0.f;
					float max_y = 0.f;

					/// Minimum dimensions permitted as widget shrinks
					float min_width = 0.f;
					float min_height = 0.f;

					/// Maximum dimensions permitted as widget grows
					float max_width = 0.f;
					float max_height = 0.f;

					bool operator==(const resize_params&);
					bool operator!=(const resize_params&);
				};

				/// <summary>Mouse cursor type.</summary>
				enum class cursor_type {
					arrow,
					hand,
					caret,
				};

			protected:
				std::string text_;
				std::string tooltip_;
				lecui::rect rect_;
				resize_params on_resize_ = { 0.f, 0.f, 0.f, 0.f };
				cursor_type cursor_ = cursor_type::arrow;
				std::string font_ = "Segoe UI";
				float font_size_ = 9.f;
				color color_text_ = { 0, 0, 0, 255 };
				color color_fill_ = { 0, 120, 170, 255 };

				/// <summary>The hit color when the mouse is over the widget.</summary>
				color color_hot_ = { 0, 120, 170, 255 };

				/// <summary>The color to be used to mark the widget as selected.</summary>
				color color_selected_ = { 0, 120, 170, 30 };

				/// <summary>The color of the widget when it is disabled.</summary>
				color color_disabled_ = { 180, 180, 180, 255 };

			public:
				specs() {};
				virtual ~specs() {};

				bool operator==(const specs&);
				bool operator!=(const specs&);

				/// <summary>Events common to all widgets.</summary>
				struct basic_events {
					/// <summary>The handler to be called when either the space bar or enter key
					/// is pressed, or if the widget is clicked.</summary>
					std::function<void()> action = nullptr;

					/// <summary>The handler to be called when the widget is clicked.</summary>
					std::function<void()> click = nullptr;

					/// <summary>The handler to be called when the widget is right-clicked.</summary>
					std::function<void()> right_click = nullptr;

					/// <summary>The handler to be called when the mouse enters the widget.</summary>
					std::function<void()> mouse_enter = nullptr;

					/// <summary>The handler to be called when the mouse leaves the widget.</summary>
					std::function<void()> mouse_leave = nullptr;
				};

				/// <summary>Get or set the widget text.</summary>
				/// <returns>A reference to the widget text.</returns>
				/// <remarks>The use of the text varies from widget to widget. Some widgets don't
				/// use this field.</remarks>
				virtual std::string& text() = 0;

				/// <summary>Get or set the widget's tooltip text.</summary>
				/// <returns>A reference to the tooltip text.</returns>
				/// <remarks>The tooltip text is displayed when the mouse is hovered over the widget.</remarks>
				virtual std::string& tooltip() = 0;

				/// <summary>Get or set the position and dimensions of the widget.</summary>
				/// <returns>A reference to the widget rectangle.</returns>
				virtual lecui::rect& rect() = 0;

				/// <summary>Get or set the behaviour of the widget when its container is resized.</summary>
				/// <returns>A reference to the resize parameters as defined in <see cref="resize_params"></see>.</returns>
				virtual resize_params& on_resize() = 0;

				/// <summary>Get or set the mouse cursor to use then over the widget.</summary>
				/// <returns>A reference to the cursor type as defined in <see cref="cursor_type"></see>.</returns>
				/// <remarks>This is only used if the widget is non-static.</remarks>
				virtual cursor_type& cursor() = 0;

				/// <summary>Get or set the default widget font, e.g. "Georgia".</summary>
				/// <returns>A reference to the widget's font name.</returns>
				virtual std::string& font() = 0;

				/// <summary>Get or set the default widget font size in points, e.g. 9.0.</summary>
				/// <returns>A reference to the widget's font size.</returns>
				virtual float& font_size() = 0;

				/// <summary>Get or set the color of the widget's text.</summary>
				/// <returns>A reference to the widget's text color.</returns>
				virtual color& color_text() = 0;

				/// <summary>Get or set the fill color of the widget.</summary>
				/// <returns>A reference to the widget's fill color.</returns>
				/// <remarks>The use of the fill color varies from widget to widget. Refer to the
				/// specific widget's documentation for details.</remarks>
				virtual color& color_fill() = 0;

				/// <summary>Get or set the widget's color when the mouse is hovered over it.</summary>
				/// <returns>A reference to the widget's hover color.</returns>
				/// <remarks>The use of the hover color varies from widget to widget. Refer to the
				/// specific widget's documentation for details.</remarks>
				virtual color& color_hot() = 0;

				/// <summary>Get or set the widget's color when selected.</summary>
				/// <returns>A reference to the widget's color when selected.</returns>
				virtual color& color_selected() = 0;

				/// <summary>Get or set the widget's color when it's disabled.</summary>
				/// <returns>A reference to the widget's color when disabled.</returns>
				virtual color& color_disabled() = 0;

				/// <summary>Widget events.</summary>
				/// <remarks>Widgets with additional events need to override this method.</remarks>
				/// <returns>A reference to the widget's basic events.</returns>
				basic_events& events() { return events_; }

				/// <summary>The widget's alias, either user defined or automatically generated by the library.</summary>
				/// <returns>The alias.</returns>
				const std::string& alias() { return alias_; }

			private:
				basic_events events_;
				std::string alias_;

				void alias(const std::string alias) {
					alias_ = alias;
				}

#if defined(LECUI_EXPORTS)
				friend class containers::page;
				friend class table_view_impl;
				friend class tree_view_impl;
				friend class html_editor_impl;
				friend class time_impl;
				friend class date_impl;
				friend class icon_impl;
#endif
			};
		}

		/// <summary>Widget management.</summary>
		class lecui_api widget_management {
		public:
			widget_management(form& fm);
			~widget_management();

			/// <summary>Enable or disable a widget.</summary>
			/// <param name="path">The full path to the widget, e.g. "home_page/username".</param>
			/// <param name="enable">Set to true to enable the widget, and false to disable it.
			/// </param>
			void enable(const std::string& path, bool enable);

			/// <summary>Show or hide a widget.</summary>
			/// <param name="path">The full path to the widget, e.g. "home_page/username".</param>
			/// <param name="show">Set to true to make the widget visible, and false to hide it.
			/// </param>
			void show(const std::string& path, bool show);

			/// <summary>Close a widget.</summary>
			/// <param name="path">The full path to the widget, e.g. "home_page/username".</param>
			/// <remarks>Avoid closing a widget from within its own handler to avoid access
			/// violation errors. Also make sure to never keep 'dangling widget references'
			/// because attempting to use those references after this method is called will
			/// result in access violation errors as well. Make sure to employ proper logic. As a
			/// failsafe, the widget is not closed immediately when this method is called. Rather
			/// a special timer is scheduled internally to close the widget. After this, the widget
			/// is closed as soon as possible, typically soon after the current handler exits.
			/// </remarks>
			void close(const std::string& path);

			/// <summary>Select a widget.</summary>
			/// <param name="path">The full path to the widget, e.g. "home_page/username".</param>
			/// <remarks>Any previous selection within the page is removed.</remarks>
			void select(const std::string& path);

		private:
			class impl;
			impl& d_;

			// Default constructor and copying an object of this class are not allowed
			widget_management() = delete;
			widget_management(const widget_management&) = delete;
			widget_management& operator=(const widget_management&) = delete;
		};
	}
}
