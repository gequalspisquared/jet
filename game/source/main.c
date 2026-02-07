/**
 * \file            main.c
 * \brief           Main source file for the game jet
 */

/*
 * MIT License
 *
 * Copyright (c) 2026 Nicholas Crane
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <jet/engine.h>

#include <stdio.h>

/*
 * TODO:
 * -[X] Create a window
 * -[ ] Create a loop and listen for events
 * -[ ] Create a graphics context
 * -[ ] Connect context to window
 * -[ ] Draw a triangle
 */

int main()
{
	printf("Hello, World!\n");

	jetInit();

	JetWindow* window = jetInitWindow(1920, 1080, "Jello");
    jetDeinitWindow(window);

    jetDeinit();

	return 0;
}