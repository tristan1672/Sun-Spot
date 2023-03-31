#pragma once
#include "GameObjClasses.hpp"
#include "Level.hpp"
#include <String>

void MultiTextureLoad(AEGfxTexture** TextureArr, unsigned int Size, std::string Str);

void MultiTextureUnload(AEGfxTexture** TextureArr, unsigned int Size);

void SingleLayerTextureSet(int i, int j, AEGfxTexture** TextureArr, int Type);

void TopLayerTextureSet(int i, int j, AEGfxTexture** TextureArr, int Type);

void MiddleLayerTextureSet(int i, int j, AEGfxTexture** TextureArr, int Type);

void BtmLayerTextureSet(int i, int j, AEGfxTexture** TextureArr, int Type);

void TextureSetNonEdge(int i, int j, AEGfxTexture** TextureArr, int Type);

void TextureSetTopEdge(int i, int j, AEGfxTexture** TextureArr, int Type);

void TextureSetBtmEdge(int i, int j, AEGfxTexture** TextureArr, int Type);