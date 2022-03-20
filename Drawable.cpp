#include "Drawable.h"
Drawable::Drawable() : color(Color::WHITE) {
};

Drawable::Drawable(Drawable& d) : color(d.color) {

};

void Drawable::setColor(Color c) {
	color = c; 
};

Color Drawable::getColor() {
	return color; 
}
