/*****************************************************************
  *  \file PlatformTexture.hpp
  *  \project name : Ready?Set.Jump!
  *  \author(s)    : Peh Zong Lin Adrian (p.zonglinadrian)
  *
  *  \brief
  *  Platform texture component.
  *  - MultiTextureLoad
  *		Loads multiple textures from file paths and stores them in the TextureArr array.
  *
  *  - MultiTextureUnload
  *		Unloads multiple textures stored in the TextureArr array.
  *
  *  - SingleLayerTextureSet
  *		Sets a single layer texture for a specified cell (i, j) using the TextureArr array.
  *
  *  - TopLayerTextureSet
  *		Sets the top layer texture for a specified cell (i, j) using the TextureArr array.
  * 
  *  - MiddleLayerTextureSet
  *		Sets the middle layer texture for a specified cell (i, j) using the TextureArr array.
  * 
  *  - BtmLayerTextureSet
  *		Sets the bottom layer texture for a specified cell (i, j) using the TextureArr array.
  * 
  *  - VerticleTextureSet
  *		Sets the vertical texture for a specified cell (i, j) using the TextureArr array.
  * 
  *  - TextureSetNonEdge
  *		Sets the given texture to a non-edge tile for a specified cell (i, j) using the TextureArr array.
  * 
  *  - TextureSetTopEdge
  *		Sets the given texture to the top edge tile for a specified cell (i, j) using the TextureArr array.
  * 
  *  - TextureSetBtmEdge
  *		Sets the given texture to the bottom tile for a specified cell (i, j) using the TextureArr array.
  * 
  *  - TextureSetLeftEdge
  *		Sets the given texture to the left edge tile for a specified cell (i, j) using the TextureArr array.
  * 
  *  - TextureSetRightEdge
  *		Sets the given texture to the right edge tile for a specified cell (i, j) using the TextureArr array.
  * 
  *  - TextureSetAll
  *		Sets the given texture to all tiles at position (i,j) using the TextureArr array.
  *
  *
  *   All content © 2023 DigiPen Institute of Technology Singapore. All rights reserved.
****************************************************************/

#pragma once
#include <String>
#include "GameObjClasses.hpp"
#include "Level.hpp"

#ifndef PLATFORM_TEXTURE_HPP
#define PLATFORM_TEXTURE_HPP

void MultiTextureLoad(AEGfxTexture** TextureArr, unsigned int Size, std::string Str);

void MultiTextureUnload(AEGfxTexture** TextureArr, unsigned int Size);

void SingleLayerTextureSet(int i, int j, AEGfxTexture** TextureArr, int Type);

void TopLayerTextureSet(int i, int j, AEGfxTexture** TextureArr, int Type);

void MiddleLayerTextureSet(int i, int j, AEGfxTexture** TextureArr, int Type);

void BtmLayerTextureSet(int i, int j, AEGfxTexture** TextureArr, int Type);

void VerticleTextureSet(int i, int j, AEGfxTexture** TextureArr, int Type);

void TextureSetNonEdge(int i, int j, AEGfxTexture** TextureArr, int Type);

void TextureSetTopEdge(int i, int j, AEGfxTexture** TextureArr, int Type);

void TextureSetBtmEdge(int i, int j, AEGfxTexture** TextureArr, int Type);

void TextureSetLeftEdge(int i, int j, AEGfxTexture** TextureArr, int Type);

void TextureSetRightEdge(int i, int j, AEGfxTexture** TextureArr, int Type);

void TextureSetAll(int i, int j, AEGfxTexture** TextureArr, int Type);

#endif // PLATFORM_TEXTURE_HPP