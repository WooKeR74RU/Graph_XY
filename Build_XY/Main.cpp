#include "Brackets.h"
#include "ExpressionTree.h"
#include "Normalize.h"
#include "Utilities.h"

//TODO: config
//TODO: display image
pair<int, int> resolution = make_pair(905, 905);
pair<int, int> xInterval = make_pair(-10, 10);
pair<int, int> yInterval = make_pair(-10, 10);

void lineTo(RenderWindow& window, const pair<int, int>& a, const pair<int, int>& b)
{
	Vertex line[] = { Vertex(Vector2f(a.first, resolution.second - a.second - 3)), Vertex(Vector2f(b.first, resolution.second - b.second - 3)) };
	window.draw(line, 2, Lines);
}

void screenshot(const RenderWindow& window)
{
	Texture texture;
	texture.create(resolution.first, resolution.second);
	texture.update(window);
	Image image = texture.copyToImage();
	image.saveToFile("graph.jpg");
}

int main()
{
	initOperations();

	fstream fin;
	fin.open("input.txt");
	string input;
	getline(fin, input);

	string expr = buildBracketsExpr(normalize(input));
	Function func(expr);

	vector<pair<int, int>> points;
	//double segment = (double)(xTo - xFrom) / resolution.first;
	for (int i = -resolution.first / 2; i < resolution.first / 2; i++)
	{
		double x = i;
		double y;
		if (!func.consider(y, x))
			continue;
		points.push_back(make_pair(i + resolution.first / 2, y + resolution.second / 2));
	}

	//vector<bool> compound(points.size() - 1);
	RenderWindow window(VideoMode(resolution.first, resolution.second), "Graph_XY");
	//window.setView(View(FloatRect(0, 0, 0, 0)));

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear();
		lineTo(window, make_pair(0, resolution.second / 2 + 1), make_pair(resolution.first, resolution.second / 2 + 1));
		lineTo(window, make_pair(resolution.first / 2 + 1, 0), make_pair(resolution.first / 2 + 1, resolution.second));
		for (int i = 0; i < points.size() - 1; i++)
			lineTo(window, points[i], points[i + 1]);
		window.display();
	}

	return 0;
}