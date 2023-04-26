void ActivateScript() {
	int key_hold_mode = VK_HOME;
	int key_exit = VK_END;
	int key_hold = VK_XBUTTON2;
	double pixel_box = 2.2555555555; // reduced pixel box size
	int pixel_sens = 90.9419;
	int pixelcolorcustom = RGB(255, 255, 85);
	COLORREF pixel_color = pixelcolorcustom;
	int leftbound = GetSystemMetrics(SM_CXSCREEN) / 2 - pixel_box;
	int rightbound = GetSystemMetrics(SM_CXSCREEN) / 2 + pixel_box;
	int topbound = GetSystemMetrics(SM_CYSCREEN) / 2 - pixel_box;
	int bottombound = GetSystemMetrics(SM_CYSCREEN) / 2 + pixel_box;
	int sleep_time = 1;

	while (true) {
		if (GetAsyncKeyState(key_hold) & 0x8000) {
			HDC hdcScreen = GetDC(NULL);
			HDC hdcMem = CreateCompatibleDC(hdcScreen);
			int width = rightbound - leftbound;
			int height = bottombound - topbound;
			BITMAPINFOHEADER bmpInfo = { 0 };
			bmpInfo.biSize = sizeof(BITMAPINFOHEADER);
			bmpInfo.biPlanes = 1;
			bmpInfo.biBitCount = 32;
			bmpInfo.biWidth = width;
			bmpInfo.biHeight = -height; // negative height to flip the image
			bmpInfo.biCompression = BI_RGB;
			LPBYTE lpBits = NULL;
			HBITMAP hBitmap = CreateDIBSection(hdcScreen, (BITMAPINFO*)&bmpInfo, DIB_RGB_COLORS, (LPVOID*)&lpBits, NULL, 0);
			if (hBitmap != NULL) {
				SelectObject(hdcMem, hBitmap);
				BitBlt(hdcMem, 0, 0, width, height, hdcScreen, leftbound, topbound, SRCCOPY);
				for (int i = 0; i < width * height; i++) {
					int r = lpBits[i * 4 + 2];
					int g = lpBits[i * 4 + 1];
					int b = lpBits[i * 4];
					if (abs(r - GetRValue(pixel_color)) < pixel_sens &&
						abs(g - GetGValue(pixel_color)) < pixel_sens &&
						abs(b - GetBValue(pixel_color)) < pixel_sens)
					{
						if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
							INPUT input = {};
							input.type = INPUT_MOUSE;
							input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
							SendInput(1, &input, sizeof(INPUT));
							Sleep(sleep_time);
						}
						break;
					}
				}
				DeleteObject(hBitmap);
			}
			DeleteDC(hdcMem);
			ReleaseDC(NULL, hdcScreen);
		}

		if (GetAsyncKeyState(key_exit) & 0x8000) {
			Sleep(400);
			break;
		}

		if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000) {
			std::cout << "EEnter pixel_box value: ";
			std::cin >> pixel_box;
			leftbound = GetSystemMetrics(SM_CXSCREEN) / 2 - pixel_box;
			rightbound = GetSystemMetrics(SM_CXSCREEN) / 2 + pixel_box;
			topbound = GetSystemMetrics(SM_CYSCREEN) / 2 - pixel_box;
			bottombound = GetSystemMetrics(SM_CYSCREEN) / 2 + pixel_box;
		}

		if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000) {
			std::cout << "EEnter pixel_sens value: ";
			std::cin >> pixel_sens;
		}

		if (GetAsyncKeyState(VK_NUMPAD3) & 0x8000) {
			std::cout << "EEnter key_hold value: ";
			std::cin >> key_hold;
		}

		if (GetAsyncKeyState(VK_NUMPAD4) & 0x8000) { // add option for changing sleep time
			std::cout << "EEnter sleep_time value: ";
			std::cin >> sleep_time;
		}

		if (GetAsyncKeyState(VK_NUMPAD5) & 0x8000) { // add option for changing sleep time
			std::cout << R"(
               COLOR-RGB-LIST-CHART
            ---------------------------
            RGB(235, 105, 254) = purple
            RGB(254, 99, 106)  = red
            RGB(255, 255, 85)  = yellow
            ---------------------------
)";
			std::cout << "EEnter RGB value: ";
			std::cin >> pixelcolorcustom;
		}

		Sleep(1);
	}
}