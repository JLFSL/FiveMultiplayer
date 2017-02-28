// Copyright 2015 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <fstream>
#include <string>

#include "include/libplatform/libplatform.h"
#include "include/v8.h"

using namespace v8;

int main(int argc, char* argv[]) {
	std::string line;
	std::string fullline;

	// Read javascript file
	{
		std::ifstream jsfile("test.js");
		if (!jsfile)
		{
			std::cout << "Error opening the javascript file" << std::endl;
			return(1);
		}

		if (jsfile.is_open())
			while (std::getline(jsfile, line))
				fullline = fullline + line;
		jsfile.close();

		std::cout << "(" << fullline.size() << "/" << fullline.max_size() << ")file output: " << fullline.c_str() << std::endl << std::endl;
	}

	// Initialize V8.
	V8::InitializeICUDefaultLocation(argv[0]);
	V8::InitializeExternalStartupData(argv[0]);
	Platform* platform = platform::CreateDefaultPlatform();
	V8::InitializePlatform(platform);
	V8::Initialize();

	// Create a new Isolate and make it the current one.
	Isolate::CreateParams create_params;
	create_params.array_buffer_allocator =
		v8::ArrayBuffer::Allocator::NewDefaultAllocator();

	Isolate* isolate = Isolate::New(create_params);
	{
		Isolate::Scope isolate_scope(isolate);

		// Create a stack-allocated handle scope.
		HandleScope handle_scope(isolate);

		// Create a new context.
		Local<Context> context = Context::New(isolate);

		// Enter the context for compiling and running the hello world script.
		Context::Scope context_scope(context);

		Local<String> source =
			String::NewFromUtf8(isolate, fullline.c_str(), NewStringType::kNormal).ToLocalChecked();

		// Compile the source code.
		Local<Script> script = Script::Compile(context, source).ToLocalChecked();

		// Run the script to get the result.
		Local<Value> result = script->Run(context).ToLocalChecked();

		// Convert the result to an UTF8 string and print it.
		String::Utf8Value utf8(result);
		printf("%s\n", *utf8);
	}
	// Dispose the isolate and tear down V8.
	isolate->Dispose();
	V8::Dispose();
	V8::ShutdownPlatform();
	delete platform;
	delete create_params.array_buffer_allocator;
	return 0;
}