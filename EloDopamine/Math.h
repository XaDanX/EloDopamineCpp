#pragma once

namespace { // Anonymous namespace to avoid LNK2005
	void MultiplySquareMatrices(float* output, float* a, float* b) {
	int size = 4 * 4;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float sum = 0.f;
			for (int k = 0; k < 4; k++)
				sum = sum + a[i * 4 + k] * b[k * 4 + j];
			output[i * 4 + j] = sum;
		}
	}
}
}