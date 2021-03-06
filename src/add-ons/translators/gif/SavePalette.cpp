////////////////////////////////////////////////////////////////////////////////
//
//	File: SavePalette.cpp
//
//	Date: December 1999
//
//	Author: Daniel Switkin
//
//	Copyright 2003 (c) by Daniel Switkin. This file is made publically available
//	under the BSD license, with the stipulations that this complete header must
//	remain at the top of the file indefinitely, and credit must be given to the
//	original author in any about box using this software.
//
////////////////////////////////////////////////////////////////////////////////

// Additional authors:	Stephan Aßmus, <superstippi@gmx.de>
//						John Scipione, <jscipione@gmail.com>


#include "SavePalette.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <new>

#include <Bitmap.h>


using std::nothrow;

extern bool debug;


// "web safe palette"
const rgb_color wsp[256] = {
	{0xff, 0xff, 0xff, 0xff}, {0xff, 0xff, 0xcc, 0xff},
	{0xff, 0xff, 0x99, 0xff}, {0xff, 0xff, 0x66, 0xff},
	{0xff, 0xff, 0x33, 0xff}, {0xff, 0xff, 0x00, 0xff},
	{0xff, 0xcc, 0xff, 0xff}, {0xff, 0xcc, 0xcc, 0xff},
	{0xff, 0xcc, 0x99, 0xff}, {0xff, 0xcc, 0x66, 0xff},
	{0xff, 0xcc, 0x33, 0xff}, {0xff, 0xcc, 0x00, 0xff},
	{0xff, 0x99, 0xff, 0xff}, {0xff, 0x99, 0xcc, 0xff},
	{0xff, 0x99, 0x99, 0xff}, {0xff, 0x99, 0x66, 0xff},
	{0xff, 0x99, 0x33, 0xff}, {0xff, 0x99, 0x00, 0xff},
	{0xff, 0x66, 0xff, 0xff}, {0xff, 0x66, 0xcc, 0xff},
	{0xff, 0x66, 0x99, 0xff}, {0xff, 0x66, 0x66, 0xff},
	{0xff, 0x66, 0x33, 0xff}, {0xff, 0x66, 0x00, 0xff},
	{0xff, 0x33, 0xff, 0xff}, {0xff, 0x33, 0xcc, 0xff},
	{0xff, 0x33, 0x99, 0xff}, {0xff, 0x33, 0x66, 0xff},
	{0xff, 0x33, 0x33, 0xff}, {0xff, 0x33, 0x00, 0xff},
	{0xff, 0x00, 0xff, 0xff}, {0xff, 0x00, 0xcc, 0xff},
	{0xff, 0x00, 0x99, 0xff}, {0xff, 0x00, 0x66, 0xff},
	{0xff, 0x00, 0x33, 0xff}, {0xff, 0x00, 0x00, 0xff},
	{0xcc, 0xff, 0xff, 0xff}, {0xcc, 0xff, 0xcc, 0xff},
	{0xcc, 0xff, 0x99, 0xff}, {0xcc, 0xff, 0x66, 0xff},
	{0xcc, 0xff, 0x33, 0xff}, {0xcc, 0xff, 0x00, 0xff},
	{0xcc, 0xcc, 0xff, 0xff}, {0xcc, 0xcc, 0xcc, 0xff},
	{0xcc, 0xcc, 0x99, 0xff}, {0xcc, 0xcc, 0x66, 0xff},
	{0xcc, 0xcc, 0x33, 0xff}, {0xcc, 0xcc, 0x00, 0xff},
	{0xcc, 0x99, 0xff, 0xff}, {0xcc, 0x99, 0xcc, 0xff},
	{0xcc, 0x99, 0x99, 0xff}, {0xcc, 0x99, 0x66, 0xff},
	{0xcc, 0x99, 0x33, 0xff}, {0xcc, 0x99, 0x00, 0xff},
	{0xcc, 0x66, 0xff, 0xff}, {0xcc, 0x66, 0xcc, 0xff},
	{0xcc, 0x66, 0x99, 0xff}, {0xcc, 0x66, 0x66, 0xff},
	{0xcc, 0x66, 0x33, 0xff}, {0xcc, 0x66, 0x00, 0xff},
	{0xcc, 0x33, 0xff, 0xff}, {0xcc, 0x33, 0xcc, 0xff},
	{0xcc, 0x33, 0x99, 0xff}, {0xcc, 0x33, 0x66, 0xff},
	{0xcc, 0x33, 0x33, 0xff}, {0xcc, 0x33, 0x00, 0xff},
	{0xcc, 0x00, 0xff, 0xff}, {0xcc, 0x00, 0xcc, 0xff},
	{0xcc, 0x00, 0x99, 0xff}, {0xcc, 0x00, 0x66, 0xff},
	{0xcc, 0x00, 0x33, 0xff}, {0xcc, 0x00, 0x00, 0xff},
	{0x99, 0xff, 0xff, 0xff}, {0x99, 0xff, 0xcc, 0xff},
	{0x99, 0xff, 0x99, 0xff}, {0x99, 0xff, 0x66, 0xff},
	{0x99, 0xff, 0x33, 0xff}, {0x99, 0xff, 0x00, 0xff},
	{0x99, 0xcc, 0xff, 0xff}, {0x99, 0xcc, 0xcc, 0xff},
	{0x99, 0xcc, 0x99, 0xff}, {0x99, 0xcc, 0x66, 0xff},
	{0x99, 0xcc, 0x33, 0xff}, {0x99, 0xcc, 0x00, 0xff},
	{0x99, 0x99, 0xff, 0xff}, {0x99, 0x99, 0xcc, 0xff},
	{0x99, 0x99, 0x99, 0xff}, {0x99, 0x99, 0x66, 0xff},
	{0x99, 0x99, 0x33, 0xff}, {0x99, 0x99, 0x00, 0xff},
	{0x99, 0x66, 0xff, 0xff}, {0x99, 0x66, 0xcc, 0xff},
	{0x99, 0x66, 0x99, 0xff}, {0x99, 0x66, 0x66, 0xff},
	{0x99, 0x66, 0x33, 0xff}, {0x99, 0x66, 0x00, 0xff},
	{0x99, 0x33, 0xff, 0xff}, {0x99, 0x33, 0xcc, 0xff},
	{0x99, 0x33, 0x99, 0xff}, {0x99, 0x33, 0x66, 0xff},
	{0x99, 0x33, 0x33, 0xff}, {0x99, 0x33, 0x00, 0xff},
	{0x99, 0x00, 0xff, 0xff}, {0x99, 0x00, 0xcc, 0xff},
	{0x99, 0x00, 0x99, 0xff}, {0x99, 0x00, 0x66, 0xff},
	{0x99, 0x00, 0x33, 0xff}, {0x99, 0x00, 0x00, 0xff},
	{0x66, 0xff, 0xff, 0xff}, {0x66, 0xff, 0xcc, 0xff},
	{0x66, 0xff, 0x99, 0xff}, {0x66, 0xff, 0x66, 0xff},
	{0x66, 0xff, 0x33, 0xff}, {0x66, 0xff, 0x00, 0xff},
	{0x66, 0xcc, 0xff, 0xff}, {0x66, 0xcc, 0xcc, 0xff},
	{0x66, 0xcc, 0x99, 0xff}, {0x66, 0xcc, 0x66, 0xff},
	{0x66, 0xcc, 0x33, 0xff}, {0x66, 0xcc, 0x00, 0xff},
	{0x66, 0x99, 0xff, 0xff}, {0x66, 0x99, 0xcc, 0xff},
	{0x66, 0x99, 0x99, 0xff}, {0x66, 0x99, 0x66, 0xff},
	{0x66, 0x99, 0x33, 0xff}, {0x66, 0x99, 0x00, 0xff},
	{0x66, 0x66, 0xff, 0xff}, {0x66, 0x66, 0xcc, 0xff},
	{0x66, 0x66, 0x99, 0xff}, {0x66, 0x66, 0x66, 0xff},
	{0x66, 0x66, 0x33, 0xff}, {0x66, 0x66, 0x00, 0xff},
	{0x66, 0x33, 0xff, 0xff}, {0x66, 0x33, 0xcc, 0xff},
	{0x66, 0x33, 0x99, 0xff}, {0x66, 0x33, 0x66, 0xff},
	{0x66, 0x33, 0x33, 0xff}, {0x66, 0x33, 0x00, 0xff},
	{0x66, 0x00, 0xff, 0xff}, {0x66, 0x00, 0xcc, 0xff},
	{0x66, 0x00, 0x99, 0xff}, {0x66, 0x00, 0x66, 0xff},
	{0x66, 0x00, 0x33, 0xff}, {0x66, 0x00, 0x00, 0xff},
	{0x33, 0xff, 0xff, 0xff}, {0x33, 0xff, 0xcc, 0xff},
	{0x33, 0xff, 0x99, 0xff}, {0x33, 0xff, 0x66, 0xff},
	{0x33, 0xff, 0x33, 0xff}, {0x33, 0xff, 0x00, 0xff},
	{0x33, 0xcc, 0xff, 0xff}, {0x33, 0xcc, 0xcc, 0xff},
	{0x33, 0xcc, 0x99, 0xff}, {0x33, 0xcc, 0x66, 0xff},
	{0x33, 0xcc, 0x33, 0xff}, {0x33, 0xcc, 0x00, 0xff},
	{0x33, 0x99, 0xff, 0xff}, {0x33, 0x99, 0xcc, 0xff},
	{0x33, 0x99, 0x99, 0xff}, {0x33, 0x99, 0x66, 0xff},
	{0x33, 0x99, 0x33, 0xff}, {0x33, 0x99, 0x00, 0xff},
	{0x33, 0x66, 0xff, 0xff}, {0x33, 0x66, 0xcc, 0xff},
	{0x33, 0x66, 0x99, 0xff}, {0x33, 0x66, 0x66, 0xff},
	{0x33, 0x66, 0x33, 0xff}, {0x33, 0x66, 0x00, 0xff},
	{0x33, 0x33, 0xff, 0xff}, {0x33, 0x33, 0xcc, 0xff},
	{0x33, 0x33, 0x99, 0xff}, {0x33, 0x33, 0x66, 0xff},
	{0x33, 0x33, 0x33, 0xff}, {0x33, 0x33, 0x00, 0xff},
	{0x33, 0x00, 0xff, 0xff}, {0x33, 0x00, 0xcc, 0xff},
	{0x33, 0x00, 0x99, 0xff}, {0x33, 0x00, 0x66, 0xff},
	{0x33, 0x00, 0x33, 0xff}, {0x33, 0x00, 0x00, 0xff},
	{0x00, 0xff, 0xff, 0xff}, {0x00, 0xff, 0xcc, 0xff},
	{0x00, 0xff, 0x99, 0xff}, {0x00, 0xff, 0x66, 0xff},
	{0x00, 0xff, 0x33, 0xff}, {0x00, 0xff, 0x00, 0xff},
	{0x00, 0xcc, 0xff, 0xff}, {0x00, 0xcc, 0xcc, 0xff},
	{0x00, 0xcc, 0x99, 0xff}, {0x00, 0xcc, 0x66, 0xff},
	{0x00, 0xcc, 0x33, 0xff}, {0x00, 0xcc, 0x00, 0xff},
	{0x00, 0x99, 0xff, 0xff}, {0x00, 0x99, 0xcc, 0xff},
	{0x00, 0x99, 0x99, 0xff}, {0x00, 0x99, 0x66, 0xff},
	{0x00, 0x99, 0x33, 0xff}, {0x00, 0x99, 0x00, 0xff},
	{0x00, 0x66, 0xff, 0xff}, {0x00, 0x66, 0xcc, 0xff},
	{0x00, 0x66, 0x99, 0xff}, {0x00, 0x66, 0x66, 0xff},
	{0x00, 0x66, 0x33, 0xff}, {0x00, 0x66, 0x00, 0xff},
	{0x00, 0x33, 0xff, 0xff}, {0x00, 0x33, 0xcc, 0xff},
	{0x00, 0x33, 0x99, 0xff}, {0x00, 0x33, 0x66, 0xff},
	{0x00, 0x33, 0x33, 0xff}, {0x00, 0x33, 0x00, 0xff},
	{0x00, 0x00, 0xff, 0xff}, {0x00, 0x00, 0xcc, 0xff},
	{0x00, 0x00, 0x99, 0xff}, {0x00, 0x00, 0x66, 0xff},
	{0x00, 0x00, 0x33, 0xff}, {0x00, 0x00, 0x00, 0xff},
	{0x00, 0x00, 0x00, 0xff}, {0x00, 0x00, 0x00, 0xff},
	{0x00, 0x00, 0x00, 0xff}, {0x00, 0x00, 0x00, 0xff},
	{0x00, 0x00, 0x00, 0xff}, {0x00, 0x00, 0x00, 0xff},
	{0x00, 0x00, 0x00, 0xff}, {0x00, 0x00, 0x00, 0xff},
	{0x00, 0x00, 0x00, 0xff}, {0x00, 0x00, 0x00, 0xff},
	{0x00, 0x00, 0x00, 0xff}, {0x00, 0x00, 0x00, 0xff},
	{0x00, 0x00, 0x00, 0xff}, {0x00, 0x00, 0x00, 0xff},
	{0x00, 0x00, 0x00, 0xff}, {0x00, 0x00, 0x00, 0xff},
	{0x00, 0x00, 0x00, 0xff}, {0x00, 0x00, 0x00, 0xff},
	{0x00, 0x00, 0x00, 0xff}, {0x00, 0x00, 0x00, 0xff},
	{0x00, 0x00, 0x00, 0xff}, {0x00, 0x00, 0x00, 0xff},
	{0x00, 0x00, 0x00, 0xff}, {0x00, 0x00, 0x00, 0xff},
	{0x00, 0x00, 0x00, 0xff}, {0x00, 0x00, 0x00, 0xff},
	{0x00, 0x00, 0x00, 0xff}, {0x00, 0x00, 0x00, 0xff},
	{0x00, 0x00, 0x00, 0xff}, {0x00, 0x00, 0x00, 0xff},
	{0x00, 0x00, 0x00, 0xff}, {0x00, 0x00, 0x00, 0xff},
	{0x00, 0x00, 0x00, 0xff}, {0x00, 0x00, 0x00, 0xff},
	{0x00, 0x00, 0x00, 0xff}, {0x00, 0x00, 0x00, 0xff},
	{0x00, 0x00, 0x00, 0xff}, {0x00, 0x00, 0x00, 0xff},
	{0x00, 0x00, 0x00, 0xff}, {0x00, 0x00, 0x00, 0xff}
};


struct ColorItem : public HashItem {
	ColorItem(unsigned int k, unsigned int c,
		uint8 r, uint8 g, uint8 b)
		:
		count(c),
		red(r),
		green(g),
		blue(b)
	{
		key = k;
	}

	unsigned int count;
	uint8 red;
	uint8 green;
	uint8 blue;
};


SavePalette::SavePalette(int mode)
	:
	pal(new(nothrow) rgb_color[256]),
	fSize(0),
	fSizeInBits(8),
	fMode(mode),
	fTransparentMode(NO_TRANSPARENCY),
	fTransparentIndex(-1),
	fBackgroundIndex(0),
	fFatalError(pal == NULL)
{
	if (IsValid()) {
		if (fMode == WEB_SAFE_PALETTE) {
			memcpy(pal, wsp, sizeof(rgb_color) * 256);
			fSize = 216;
		} else if (fMode == BEOS_SYSTEM_PALETTE) {
			color_map* map = (color_map*)system_colors();
			memcpy(pal, map->color_list, sizeof(rgb_color) * 256);
			fSize = 256;
		} else if (fMode == GREYSCALE_PALETTE) {
			for (int i = 0; i < 256; i++) {
				pal[i].red = pal[i].green = pal[i].blue = i;
				pal[i].alpha = 0xff;
			}
			fSize = 256;
		}
	}
}


static int
make_key(uint8 r, uint8 g, uint8 b, uint8 bits)
{
	r = r >> (8 - bits);
	g = g >> (8 - bits);
	b = b >> (8 - bits);

	return (r << (bits * 2)) | (g << bits) | b;
}


static bool
touch_color_item(SFHash& hash, unsigned int key, uint8 r, uint8 g, uint8 b)
{
	ColorItem* ci = (ColorItem*)hash.GetItem(key);
	if (ci == NULL) {
		ci = new(nothrow) ColorItem(key, 1, r, g, b);
		if (ci == NULL) {
			if (debug)
				printf("Out of memory in touch_color_item()\n");
			return false;
		}
		hash.AddItem((HashItem*)ci);
	} else {
		ci->count++;
#if 0
		// use brightest color
		ci->red = max_c(ci->red, r);
		ci->green = max_c(ci->green, g);
		ci->blue = max_c(ci->blue, b);
#endif
	}
	return true;
}


SavePalette::SavePalette(BBitmap* bitmap, int32 maxSizeInBits)
	:
	pal(new(nothrow) rgb_color[256]),
	fSize(0),
	fSizeInBits(0),
	fMode(OPTIMAL_PALETTE),
	fTransparentMode(NO_TRANSPARENCY),
	fTransparentIndex(-1),
	fBackgroundIndex(0),
	fFatalError(pal == NULL)
{
	if (!IsValid())
		return;

	SFHash hash(1 << 16);
	if (hash.fatalerror) {
		if (debug)
			printf("Out of memory in SavePalette(BBitmap*)\n");
		fFatalError = true;
		return;
	}

	// reject unsupported color spaces
	// TODO: B_CMAP8 and B_GRAY8 should be really easy to support as well!!
	color_space cs = bitmap->ColorSpace();
	if (cs != B_RGB32 && cs != B_RGBA32 && cs != B_RGB32_BIG
		&& cs != B_RGBA32_BIG) {
		if (debug) {
			printf("Wrong color space given in SavePalette(BBitmap):\n");
			printf("%d %d %d %d or 0x%x\n",
				(cs & 0xff000000) >> 24, (cs & 0xff0000) >> 16,
				(cs & 0xff00) >> 8, cs & 0xff, cs);
		}
		fFatalError = true;
		return;
	}

	BRect rect = bitmap->Bounds();
	uint32 height = rect.IntegerHeight() + 1;
	uint32 width = rect.IntegerWidth() + 1;
	uint8* bits = (uint8*)bitmap->Bits();
	uint32 bpr = bitmap->BytesPerRow();

	uint8 r;
	uint8 g;
	uint8 b;
	uint8 useBits = 3 + maxSizeInBits / 2;
	if (cs == B_RGB32 || cs == B_RGBA32) {
		for (uint32 y = 0; y < height; y++) {
			uint8* handle = bits;
			for (uint32 x = 0; x < width; x++) {
				b = handle[0];
				g = handle[1];
				r = handle[2];
				handle += 4;

				uint32 key = make_key(r, g, b, useBits);
				if (!touch_color_item(hash, key, r, g, b)) {
					if (debug)
						printf("Out of memory in SavePalette(BBitmap*)\n");

					fFatalError = true;
					return;
				}
			}
			bits += bpr;
		}
	} else if ((cs == B_RGB32_BIG || cs == B_RGBA32_BIG)) {
		for (uint32 y = 0; y < height; y++) {
			uint8* handle = bits;
			for (uint32 x = 0; x < width; x++) {
				b = handle[2];
				g = handle[1];
				r = handle[0];
				handle += 4;

				uint32 key = make_key(r, g, b, useBits);
				if (!touch_color_item(hash, key, r, g, b)) {
					if (debug)
						printf("Out of memory in SavePalette(BBitmap*)\n");
					fFatalError = true;
					return;
				}
			}
			bits += bpr;
		}
	}

	int unique_colors = hash.CountItems();
	while (((1 << fSizeInBits) < unique_colors)
		&& (fSizeInBits < maxSizeInBits)) {
		fSizeInBits++;
	}
	fSize = 1 << fSizeInBits;

	ColorItem** topcolors = (ColorItem**)malloc(fSize * sizeof(ColorItem*));
	if (topcolors == NULL) {
		if (debug) printf("Out of memory in SavePalette(BBitmap*)\n");
		fFatalError = true;
		return;
	}
	ColorItem* dummy = new ColorItem(0, 0, 0, 0, 0);
	for (int i = 0; i < fSize; i++)
		topcolors[i] = dummy;

	for (int i = 0; i < unique_colors; i++) {
		ColorItem* ci = (ColorItem*)hash.NextItem();
		for (int j = 0; j < fSize; j++) {
			if (ci->count > topcolors[j]->count) {
				for (int k = fSize - 1; k > j; k--) {
					topcolors[k] = topcolors[k - 1];
				}
				topcolors[j] = ci;
				break;
			}
		}
	}

	for (int i = 0; i < fSize; i++) {
		pal[i].red = topcolors[i]->red;
		pal[i].green = topcolors[i]->green;
		pal[i].blue = topcolors[i]->blue;
		pal[i].alpha = 0xff;
	}

	delete dummy;
	free(topcolors);
}


SavePalette::~SavePalette()
{
	delete[] pal;
}


uint8
SavePalette::IndexForColor(uint8 red, uint8 green, uint8 blue, uint8 alpha)
{
	// standard mapping services once a palette is loaded
	if (fTransparentMode > NO_TRANSPARENCY && alpha < 128)
		return fTransparentIndex;

	uint8 index = 0;

	if (fMode == GREYSCALE_PALETTE) {
		index = (308 * red + 600 * green + 116 * blue) / 1024;
		// avoid transparent index
		if (fTransparentMode == AUTO_TRANSPARENCY && index == 1
			&& fTransparentIndex == 1) {
			index = 0;
		}
	} else {
		int closestDistance = 255 * 255 * 3;
	
		if (fTransparentMode == AUTO_TRANSPARENCY) {
			for (int i = 0; i < fTransparentIndex && closestDistance != 0;
					i++) {
				int rd = (int)red - (int)pal[i].red;
				int gd = (int)green - (int)pal[i].green;
				int bd = (int)blue - (int)pal[i].blue;
				int distanceAtIndex = rd * rd + gd * gd + bd * bd;
				if (distanceAtIndex < closestDistance) {
					closestDistance = distanceAtIndex;
					index = i;
				}
			}
			for (int i = fTransparentIndex + 1;
					i < fSize && closestDistance != 0; i++) {
				int rd = (int)red - (int)pal[i].red;
				int gd = (int)green - (int)pal[i].green;
				int bd = (int)blue - (int)pal[i].blue;
				int distanceAtIndex = rd * rd + gd * gd + bd * bd;
				if (distanceAtIndex < closestDistance) {
					closestDistance = distanceAtIndex;
					index = i;
				}
			}
		} else {
			for (int i = 0; i < fSize && closestDistance != 0; i++) {
				int rd = (int)red - (int)pal[i].red;
				int gd = (int)green - (int)pal[i].green;
				int bd = (int)blue - (int)pal[i].blue;
				int distanceAtIndex = rd * rd + gd * gd + bd * bd;
				if (distanceAtIndex < closestDistance) {
					closestDistance = distanceAtIndex;
					index = i;
				}
			}
		}
	}

	return index;
}


void
SavePalette::PrepareForAutoTransparency()
{
	fTransparentMode = AUTO_TRANSPARENCY;
	// TODO: in the SavePalette::SavePalette(BBitmap*),
	// we don't use more colors than necessary, however,
	// here we take a slot away for transparency, even if
	// we might still have used less colors than the user
	// wanted as a maximum
	// NOTE: the last index
	switch (fMode) {
		case WEB_SAFE_PALETTE:
			fTransparentIndex = 216;
			fSize = 217;
			break;
		case BEOS_SYSTEM_PALETTE:
			fTransparentIndex = 0;
			break;
		case GREYSCALE_PALETTE:
			fTransparentIndex = 1;
			break;
		case OPTIMAL_PALETTE:
			fTransparentIndex = fSize - 1;
			break;
	}
}


void
SavePalette::SetTransparentColor(uint8 red, uint8 green, uint8 blue)
{
	fTransparentMode = COLOR_KEY_TRANSPARENCY;

	bool found = false;
	// try direct hit first
	for (int i = 0; i < fSize; i++) {
		if (pal[i].red == red &&
			pal[i].green == green &&
			pal[i].blue == blue) {

			fTransparentIndex = i;
			found = true;

			break;
		}
	}
	if (!found) {
		// find closest match
		fTransparentIndex = IndexForColor(red, green, blue);
		// NOTE: This is a tough decision:
		// -> the exact color might be contained within the image
		//    but have slipped through the net and is now not in the
		//    palette, the user still wants those pixels to be
		//    transparent of course, so it is best to match up a
		//    color from the palette
		// -> on the other hand, the setting might still be there
		//    from some previous image and the color might not
		//    even appear in the current image at all... but I guess
		//    handling it like below is the lesser evil.
		// match up color at index to provided transparent color,
		// to make sure it actually works
		pal[fTransparentIndex].red = red;
		pal[fTransparentIndex].green = green;
		pal[fTransparentIndex].blue = blue;
		found = true;
	}
}


void
SavePalette::GetColors(uint8* buffer, int size) const
{
	int maxIndex = max_c(size / 3, fSize) - 1;
	for (int i = 0; i <= maxIndex; i++) {
		*buffer++ = pal[i].red;
		*buffer++ = pal[i].green;
		*buffer++ = pal[i].blue;
	}
	int rest = (maxIndex + 1) * 3;
	if (rest < size)
		memset(buffer, 0, size - rest);
}
