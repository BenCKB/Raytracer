#include "Image.h"

Image::Image(int width, int height) {

	for (int i = 0; i < (width * height); ++i) {
		Colour c(0.0, 0.0, 0.0);
		m_data.push_back(c);
	}

	m_width = width;
	m_height = height;
}

Image::~Image() {}

Colour* Image::at(int x, int y){
	return &m_data[m_width * y + x];
}

void Image::set(int x, int y, const Colour& c){
	Colour* data = at(x, y);
	data->a = c.a;
	data->r = c.r;
	data->g = c.g;
	data->b = c.b;
}

bool Image::save(std::string path) {
	std::string absPath = path + "output.png";
	uint8_t* output_data = new uint8_t[m_width * m_height * 4];

	int index = 0;
	for (int j = m_height - 1; j >= 0; --j)
	{
		for (int i = 0; i < m_width; ++i)
		{
			output_data[index++] = (unsigned char)(255.0f * Util::clamp(at(i, j)->r));
			output_data[index++] = (unsigned char)(255.0f * Util::clamp(at(i, j)->g));
			output_data[index++] = (unsigned char)(255.0f * Util::clamp(at(i, j)->b));
			output_data[index++] = (unsigned char)(255.0f * Util::clamp(at(i, j)->a));
		}
	}
	stbi_flip_vertically_on_write(1);
	stbi_write_png(absPath.c_str(), m_width, m_height, 4, output_data, m_width * 4);

	delete[] output_data;

	return true;

}

const Colour Colour::BLACK(0, 0, 0);
