/*****************************************************************
  *  \file PlatformTexture.cpp
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

#include "PlatformTexture.hpp"

/*****************************************************************
 * \brief
 *		Loads multiple textures from file paths and stores them in the TextureArr array.
 * 
 * \param TextureArr 
 *		Pointer to an array of AEGfxTexture pointers to be filled with loaded textures.
 * 
 * \param Size 
 *		The number of textures to be loaded.
 * 
 * \param Str 
 *		The file path and name prefix for each texture file to be loaded.
****************************************************************/
void MultiTextureLoad(AEGfxTexture** TextureArr, unsigned int Size, std::string Str) {
	for (int i{}; i < Size; ++i) {
		std::string location{};
		location += Str + std::to_string(i + 1) + ".png";
		TextureArr[i] = AEGfxTextureLoad(location.c_str());
	}
}

/*****************************************************************
 * \brief
 *		Unloads multiple textures stored in the TextureArr array.
 *
 * \param TextureArr 
 *		Pointer to an array of AEGfxTexture pointers to be unloaded.
 *
 * \param Size
 *		The number of textures to be unloaded.
****************************************************************/
void MultiTextureUnload(AEGfxTexture** TextureArr, unsigned int Size) {
	for (int i{}; i < Size; ++i) {
		AEGfxTextureUnload(TextureArr[i]);
	}
}

/*****************************************************************
 * \brief
 *		Sets a single layer texture for a specified cell (i, j) using the TextureArr array.
 *
 * \param i
 *		The row index of the cell to set the texture for.
 *
 * \param j
 *		The column index of the cell to set the texture for.
 *
 * \param TextureArr
 *		Pointer to an array of AEGfxTexture pointers to choose the texture 
 * 
 * \param Type
 *		The index of the texture to set for the cell.
****************************************************************/
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

/*****************************************************************
 * \brief
 *		Sets the top layer texture for a specified cell (i, j) using the TextureArr array.
 *
 * \param i
 *		The row index of the cell to set the texture for.
 *
 * \param j
 *		The column index of the cell to set the texture for.
 *
 * \param TextureArr
 *		Pointer to an array of AEGfxTexture pointers to choose the texture
 *
 * \param Type
 *		The index of the texture to set for the cell.
****************************************************************/
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

/*****************************************************************
 * \brief
 *		Sets the middle layer texture for a specified cell (i, j) using the TextureArr array.
 *
 * \param i
 *		The row index of the cell to set the texture for.
 *
 * \param j
 *		The column index of the cell to set the texture for.
 *
 * \param TextureArr
 *		Pointer to an array of AEGfxTexture pointers to choose the texture
 *
 * \param Type
 *		The index of the texture to set for the cell.
****************************************************************/
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

/*****************************************************************
 * \brief
 *		Sets the bottom layer texture for a specified cell (i, j) using the TextureArr array.
 *
 * \param i
 *		The row index of the cell to set the texture for.
 *
 * \param j
 *		The column index of the cell to set the texture for.
 *
 * \param TextureArr
 *		Pointer to an array of AEGfxTexture pointers to choose the texture
 *
 * \param Type
 *		The index of the texture to set for the cell.
****************************************************************/
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

/*****************************************************************
 * \brief
 *		Sets the vertical texture for a specified cell (i, j) using the TextureArr array.
 *
 * \param i
 *		The row index of the cell to set the texture for.
 *
 * \param j
 *		The column index of the cell to set the texture for.
 *
 * \param TextureArr
 *		Pointer to an array of AEGfxTexture pointers to choose the texture
 *
 * \param Type
 *		The index of the texture to set for the cell.
****************************************************************/
void VerticleTextureSet(int i, int j, AEGfxTexture** TextureArr, int Type) {
	if (platform[i - 1][j].GetPlatformType() == Type) { // Top is
		if (platform[i + 1][j].GetPlatformType() == Type) // Btm is
			platform[i][j].SetTexture(TextureArr[4]); // Top is, btm is = Verticle middle
		else
			platform[i][j].SetTexture(TextureArr[5]); // Top is, btm not = Verticle btm
	}
	else {
		if (platform[i + 1][j].GetPlatformType() == Type) // Btm is
			platform[i][j].SetTexture(TextureArr[3]); // Verticle top
		else
			platform[i][j].SetTexture(TextureArr[15]); // Single block
	}
}

/*****************************************************************
 * \brief
 *		Sets the given texture to a non-edge tile for a specified cell (i, j) using the TextureArr array.
 *
 * \param i
 *		The row index of the cell to set the texture for.
 *
 * \param j
 *		The column index of the cell to set the texture for.
 *
 * \param TextureArr
 *		Pointer to an array of AEGfxTexture pointers to choose the texture
 *
 * \param Type
 *		The index of the texture to set for the cell.
****************************************************************/
void TextureSetNonEdge(int i, int j, AEGfxTexture** TextureArr, int Type) {
	if (platform[i - 1][j].GetPlatformType() != Type) { // If above is not			
		if (platform[i + 1][j].GetPlatformType() != Type) // Above not, below not = single layer
			SingleLayerTextureSet(i, j, TextureArr, Type); // Single layer
		else // Above not, btm is
			TopLayerTextureSet(i, j, TextureArr, Type); // Top layer
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

/*****************************************************************
 * \brief
 *		Sets the given texture to the top edge tile for a specified cell (i, j) using the TextureArr array.
 *
 * \param i
 *		The row index of the cell to set the texture for.
 *
 * \param j
 *		The column index of the cell to set the texture for.
 *
 * \param TextureArr
 *		Pointer to an array of AEGfxTexture pointers to choose the texture
 *
 * \param Type
 *		The index of the texture to set for the cell.
****************************************************************/
void TextureSetTopEdge(int i, int j, AEGfxTexture** TextureArr, int Type) {
	if (platform[i + 1][j].GetPlatformType() == Type) { // Btm is
		if (j == 0) { // Top left
			if (platform[i][j + 1].GetPlatformType() == Type) // Right is
				platform[i][j].SetTexture(TextureArr[6]); // Btm is, right is = Top layer left block
			else
				platform[i][j].SetTexture(TextureArr[3]); // Btm is, right not = Verticle row top block
		}
		else if (j == e_binaryMapWidth - 1) { // Top right
			if (platform[i][j - 1].GetPlatformType() == Type) // Left is
				platform[i][j].SetTexture(TextureArr[8]); // Btm is, left is = Top layer right block
			else
				platform[i][j].SetTexture(TextureArr[3]); // Btm is, left not = Verticle row top block
		}
		else 
			TopLayerTextureSet(i, j, TextureArr, Type); // Top layer
	}
	else {// Btm not (Single layer / vertial row)
		if (j == 0) { // Top left 
			if (platform[i][j + 1].GetPlatformType() == Type) // Right is
				platform[i][j].SetTexture(TextureArr[0]); // Btm not, right is = Single layer left block
			else
				platform[i][j].SetTexture(TextureArr[15]); // Btm not, right not = Single block
		}
		else if (j == e_binaryMapWidth - 1) { // Top right
			if (platform[i][j - 1].GetPlatformType() == Type) // Left is
				platform[i][j].SetTexture(TextureArr[2]); // Btm not, left is = Single layer right block
			else
				platform[i][j].SetTexture(TextureArr[15]); // Btm not, left not = Single block
		}
		else
			SingleLayerTextureSet(i, j, TextureArr, Type); // Single layer
	}
}

/*****************************************************************
 * \brief
 *		Sets the given texture to the bottom tile for a specified cell (i, j) using the TextureArr array.
 *
 * \param i
 *		The row index of the cell to set the texture for.
 *
 * \param j
 *		The column index of the cell to set the texture for.
 *
 * \param TextureArr
 *		Pointer to an array of AEGfxTexture pointers to choose the texture
 *
 * \param Type
 *		The index of the texture to set for the cell.
****************************************************************/
void TextureSetBtmEdge(int i, int j, AEGfxTexture** TextureArr, int Type) {
	if (platform[i - 1][j].GetPlatformType() == Type) {// Above is
		if (j == 0) { // Btm left
			if (platform[i][j + 1].GetPlatformType() == Type) // Right is
				platform[i][j].SetTexture(TextureArr[12]); // Top is, right is = Btm layer left block
			else
				platform[i][j].SetTexture(TextureArr[5]); // Btm is, right not = Verticle row btm block
		}
		else if (j == e_binaryMapWidth - 1) { // Btm right
			if (platform[i][j - 1].GetPlatformType() == Type) // Left is
				platform[i][j].SetTexture(TextureArr[14]); // Btm is, left is = Btm layer right block
			else
				platform[i][j].SetTexture(TextureArr[5]); // Btm is, left not = Verticle row btm block
		}
		else
			BtmLayerTextureSet(i, j, TextureArr, Type); // Btm layer
	}
	else {// Above not (Single layer / vertial row)
		if (j == 0) { // Btm left 
			if (platform[i][j + 1].GetPlatformType() == Type) // Right is
				platform[i][j].SetTexture(TextureArr[0]); // Top not, right is = Single layer left block
			else
				platform[i][j].SetTexture(TextureArr[15]); // Top not, right not = Single block
		}
		else if (j == e_binaryMapWidth - 1) { // Btm right
			if (platform[i][j - 1].GetPlatformType() == Type) // Left is
				platform[i][j].SetTexture(TextureArr[2]); // Top not, left is = Single layer right block
			else
				platform[i][j].SetTexture(TextureArr[15]); // Top not, left not = Single block
		}
		else
			SingleLayerTextureSet(i, j, TextureArr, Type); // Single layer
	}
}

/*****************************************************************
 * \brief
 *		Sets the given texture to the left edge tile for a specified cell (i, j) using the TextureArr array.
 *
 * \param i
 *		The row index of the cell to set the texture for.
 *
 * \param j
 *		The column index of the cell to set the texture for.
 *
 * \param TextureArr
 *		Pointer to an array of AEGfxTexture pointers to choose the texture
 *
 * \param Type
 *		The index of the texture to set for the cell.
****************************************************************/
void TextureSetLeftEdge(int i, int j, AEGfxTexture** TextureArr, int Type) {

	if (platform[i][j + 1].GetPlatformType() == Type) { // Right is
		// Left block
		if (i == 0) { // Top left corner
			if (platform[i + 1][j].GetPlatformType() == Type) // Btm is
				platform[i][j].SetTexture(TextureArr[6]); // Btm is, right is = Top layer left block
			else
				platform[i][j].SetTexture(TextureArr[0]); // Btm not, right is = Single row left block
		}
		else if (i == e_binaryMapHeight - 1) { // Btm left corner
			if (platform[i - 1][j].GetPlatformType() == Type) // Top is
				platform[i][j].SetTexture(TextureArr[12]); // Top is, right is = Btm layer left block
			else
				platform[i][j].SetTexture(TextureArr[0]); // Top not, right is = Single row left block
		}
		else if (platform[i - 1][j].GetPlatformType() == Type) { // Top is
			if (platform[i + 1][j].GetPlatformType() == Type) // Btm is
				platform[i][j].SetTexture(TextureArr[9]); // Top is, btm is = Middle layer left block
			else
				platform[i][j].SetTexture(TextureArr[12]); // Top is, btm not = Btm layer left block
		}
		else {
			if (platform[i + 1][j].GetPlatformType() == Type) // Btm is
				platform[i][j].SetTexture(TextureArr[6]); // Top layer
			else
				platform[i][j].SetTexture(TextureArr[0]); // Single layer
		}
	}
	else { // Right not = Verticle Row
		if (i == 0) { // Top left
			if (platform[i + 1][j].GetPlatformType() == Type) // Btm is
				platform[i][j].SetTexture(TextureArr[3]); // Btm is, right not = Verticle top block
			else 
				platform[i][j].SetTexture(TextureArr[15]); // Btm not, right not = Single block
		}
		else if (i == e_binaryMapHeight - 1) { // Btm left
			if (platform[i - 1][j].GetPlatformType() == Type) // Top is
				platform[i][j].SetTexture(TextureArr[5]); // Top is, right not = Verticle btm block
			else
				platform[i][j].SetTexture(TextureArr[15]); // Top not, right not = Single block
		}
		else 
			VerticleTextureSet(i, j, TextureArr, Type);
	}
}

/*****************************************************************
 * \brief
 *		Sets the given texture to the right edge tile for a specified cell (i, j) using the TextureArr array.
 *
 * \param i
 *		The row index of the cell to set the texture for.
 *
 * \param j
 *		The column index of the cell to set the texture for.
 *
 * \param TextureArr
 *		Pointer to an array of AEGfxTexture pointers to choose the texture
 *
 * \param Type
 *		The index of the texture to set for the cell.
****************************************************************/
void TextureSetRightEdge(int i, int j, AEGfxTexture** TextureArr, int Type) {
	if (platform[i][j - 1].GetPlatformType() == Type) { // Left is
		// Right block
		if (i == 0) { // Btm right corner
			if (platform[i + 1][j].GetPlatformType() == Type) // Btm is
				platform[i][j].SetTexture(TextureArr[10]); // Btm is, left is = Top layer right block
			else
				platform[i][j].SetTexture(TextureArr[2]); // Btm not, left is = Single row right block
		}
		else if (i == e_binaryMapHeight - 1) { // Btm right corner
			if (platform[i - 1][j].GetPlatformType() == Type) // Top is
				platform[i][j].SetTexture(TextureArr[14]); // Top is, left is = Btm layer right block
			else
				platform[i][j].SetTexture(TextureArr[2]); // Top not, left is = Single row right block
		}
		else if (platform[i - 1][j].GetPlatformType() == Type) { // Top is
			if (platform[i + 1][j].GetPlatformType() == Type) // Btm is
				platform[i][j].SetTexture(TextureArr[11]); // Top is, btm is = Middle layer
			else
				platform[i][j].SetTexture(TextureArr[14]); // Top is, btm not = Btm layer
		}
		else {
			if (platform[i + 1][j].GetPlatformType() == Type) // Btm is
				platform[i][j].SetTexture(TextureArr[8]); // Top layer
			else
				platform[i][j].SetTexture(TextureArr[2]); // Single layer
		}
	}
	else { // Left not = Verticle row
		if (i == 0) { // Top right
			if (platform[i + 1][j].GetPlatformType() == Type) // Btm is
				platform[i][j].SetTexture(TextureArr[3]); // Btm is, left not = Verticle top block
			else
				platform[i][j].SetTexture(TextureArr[15]); // Btm not, left not = Single block
		}
		else if (i == e_binaryMapHeight - 1) { // Btm right
			if (platform[i - 1][j].GetPlatformType() == Type) // Top is
				platform[i][j].SetTexture(TextureArr[5]); // Top is, left not = Verticle btm block
			else
				platform[i][j].SetTexture(TextureArr[15]); // Top not, left not = Single block
		}
		else
			VerticleTextureSet(i, j, TextureArr, Type);
	}
}

/*****************************************************************
 * \brief
 *		Sets the given texture to all tiles at position (i,j) using the TextureArr array.
 *
 * \param i
 *		The row index of the cell to set the texture for.
 *
 * \param j
 *		The column index of the cell to set the texture for.
 *
 * \param TextureArr
 *		Pointer to an array of AEGfxTexture pointers to choose the texture
 *
 * \param Type
 *		The index of the texture to set for the cell.
****************************************************************/
void TextureSetAll(int i, int j, AEGfxTexture** TextureArr, int Type) {
	if (i == 0) {
		TextureSetTopEdge(i, j, TextureArr, Type);
	}
	else if (i == e_binaryMapHeight - 1) {
		TextureSetBtmEdge(i, j, TextureArr, Type);
	}
	else if (j == 0) {
		TextureSetLeftEdge(i, j, TextureArr, Type);
	}
	else if (j == e_binaryMapWidth - 1) {
		TextureSetRightEdge(i, j, TextureArr, Type);
	}
	else {
		TextureSetNonEdge(i, j, TextureArr, Type);
	}
}