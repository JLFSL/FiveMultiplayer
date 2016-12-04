#pragma once

#ifdef _WIN32
// Win
#include <Windows.h>
#include <list>
#include <sstream>
#include <iostream>
#include <string>

// CEF
#include "include/cef_app.h"
#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/cef_render_handler.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_helpers.h"
#include "include/wrapper/cef_closure_task.h"

// CEF Windows
#include "CEFLauncher.h"
#include "CEFLauncher_Handler.h"
#endif

