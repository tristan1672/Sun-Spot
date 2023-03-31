#include "PlatformTexture.hpp"

void MultiTextureLoad(AEGfxTexture** TextureArr, unsigned int Size, std::string Str) {
	for (int i{}; i < Size; ++i) {
		std::string location{};
		location += Str + std::to_string(i + 1) + ".png";
		TextureArr[i] = AEGfxTextureLoad(location.c_str());
	}
}

void MultiTextureUnload(AEGfxTexture** TextureArr, unsigned int Size) {
	for (int i{}; i < Size; ++i) {
		AEGfxTextureUnload(TextureArr[i]);
	}
}

void SingleLayerTextureSet(int i, int j, AEGfxTexture** TextureArr, int Type) {
	if (platform[i][j - 1].GetPlatformType() == Type) { // Left is

		if (platform[i][j + 1].GetPlatformType() == Type) // Right is
			platform[i][j].SetTexture(TextureArr[1]); // Left is, right is = single layer center block
		else
			platform[i][j].SetTexture(TextureArr[2]); // Left is, right not = Right most block of single layer
	}
	else {
		if (platform[i][j + 1].GetPlatformType() == Type) // Right is
			platform[i][j].SetTexture(TextureArr[0]); // Left not, right is = Left most block of single layer
		else
			platform[i][j].SetTexture(TextureArr[15]); // Single block
	}
}

void TopLayerTextureSet(int i, int j, AEGfxTexture** TextureArr, int Type) {
	if (platform[i][j - 1].GetPlatformType() == Type) { // Left is

		if (platform[i][j + 1].GetPlatformType() == Type)  // Right is
			platform[i][j].SetTexture(TextureArr[7]); // Left is, right is = Top center block
		else
			platform[i][j].SetTexture(TextureArr[8]);  // Left is, right not = Top right block
	}
	else { // Left not
		if (platform[i][j + 1].GetPlatformType() == Type)  // Right is
			platform[i][j].SetTexture(TextureArr[6]); // Left not, right is = Top left block
		else // Verticle Row
			platform[i][j].SetTexture(TextureArr[3]); // Left not, right not = Vetical top
	}
}

void MiddleLayerTextureSet(int i, int j, AEGfxTexture** TextureArr, int Type) {
	if (platform[i][j - 1].GetPlatformType() == Type) { // Left is

		if (platform[i][j + 1].GetPlatformType() == Type)  // Right is
			platform[i][j].SetTexture(TextureArr[10]); // Left is, right is = middle layer center block
		else
			platform[i][j].SetTexture(TextureArr[11]); // Left is, right not = Right most block of middle layer
	}
	else { // Left not
		if (platform[i][j + 1].GetPlatformType() == Type)  // Right is
			platform[i][j].SetTexture(TextureArr[9]); // Left not, right is = Middle left block
		else // Verticle Row
			platform[i][j].SetTexture(TextureArr[4]); // Left not, right not = Vetical middle
	}
}

void BtmLayerTextureSet(int i, int j, AEGfxTexture** TextureArr, int Type) {
	if (platform[i][j - 1].GetPlatformType() == Type) { // Left is

		if (platform[i][j + 1].GetPlatformType() == Type)  // Right is
			platform[i][j].SetTexture(TextureArr[13]); // Left is, right is = btm layer center block
		else
			platform[i][j].SetTexture(TextureArr[14]); // Left is, right not = Right most block of btm layer
	}
	else { // Left not
		if (platform[i][j + 1].GetPlatformType() == Type)  // Right is
			platform[i][j].SetTexture(TextureArr[12]); // Left not, right is = Btm left block
		else // Verticle Row
			platform[i][j].SetTexture(TextureArr[5]); // Left not, right not = Vetical btm
	}
}

//
void TextureSetNonEdge(int i, int j, AEGfxTexture** TextureArr, int Type) {
	if (platform[i - 1][j].GetPlatformType() != Type) { // If above is not			
		if (platform[i + 1][j].GetPlatformType() != Type) { // Above not, below not = single layer
			// Single layer
			SingleLayerTextureSet(i, j, TextureArr, Type);
		}
		else { // Above not, btm is
			// Top layer
			TopLayerTextureSet(i, j, TextureArr, Type);
		}
	}
	else if (platform[i + 1][j].GetPlatformType() != Type) { // Above is , below not = btm layer
		// Btm layer
		BtmLayerTextureSet(i, j, TextureArr, Type);
	}
	else {
		// Middle layer
		MiddleLayerTextureSet(i, j, TextureArr, Type);
	}
}

void TextureSetTopEdge(int i, int j, AEGfxTexture** TextureArr, int Type) {
	if (platform[i + 1][j].GetPlatformType() == Type) { // Btm is
		// Top layer
		TopLayerTextureSet(i, j, TextureArr, Type);
	}
	else { // Btm not
		// Single layer
		SingleLayerTextureSet(i, j, TextureArr, Type);
	}
}

void TextureSetBtmEdge(int i, int j, AEGfxTexture** TextureArr, int Type) {
	if (platform[i - 1][j].GetPlatformType() == Type) { // Above is
		// Btm layer
		BtmLayerTextureSet(i, j, TextureArr, Type);
	}
	else { // Above not
		// Single layer
		SingleLayerTextureSet(i, j, TextureArr, Type);
	}
}



