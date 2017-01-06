#pragma once

// Windows Libraries
#include <windows.h>

// C++ Libraries
#include <string>
#include <sstream>
#include <list>
#include <vector>

// Vendor
	// Vendor.CEF
	#include <include/cef_app.h>
	#include <include/cef_base.h>
	#include <include/cef_client.h>
	#include <include/cef_render_handler.h>
	#include <include/cef_sandbox_win.h>
	#include <include/cef_browser.h>
	#include <include/cef_command_line.h>

	#include <include/views/cef_browser_view.h>
	#include <include/views/cef_window.h>

	#include <include/wrapper/cef_helpers.h>
	#include <include/wrapper/cef_closure_task.h>

	#include <include/base/cef_bind.h>

// CoreCEF
#include "CCef.h"