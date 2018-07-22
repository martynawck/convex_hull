-	Martyna Wi¹cek 249481
- 	Problem do rozwi¹zania polega³ na znalezieniu pow³oki wypuk³ej dla zadanego zbiorów punktów w przestrzeni trójwymiarowej z zadan¹ dok³adnoœci¹.
	Dok³adnoœæ jest opisywana przez dzia³anie funkcji Minimizer, która dla wygenerowanego zbioru punktów jest w stanie ograniczyæ go metod¹ wokselizacji.
	Algorytmy zastosowane w programie to algorytm przyrostowy i QuickHull.
-	Dane wejœciowe to w pierwszym wierszu wspó³rzêdne œrodka ciê¿koœci bry³y, na której opiera siê generacja punktów oraz w kolejnych liniach wspó³rzêdne x,y,z punktu.
	Prezentacja wyników odbywa siê za pomoc¹ wyœwietlenia powsta³ych œcian bry³y w OpenGl.
-	Algorytmami, których u¿y³am do obliczenia otoczki wypuk³ej s¹ QuickHull oraz IncrementalHull. Przechowywane œciany bry³y znajduj¹ siê w vectorze facets w klasie ConvexHull.
-	ConvexHull.h -> klasa, opisuj¹ca obiekt otoczi wypuk³ej, znajduj¹ siê w niej œciany bry³y oraz podstawowe metody
	Edge.h -> klasa opisuj¹ca krawêdz trójk¹ta, który jest tworzony przy budowaniu otoczki.
	Facet.h -> klasa opisuj¹ca œcianê otoczki czyli "trójk¹t"
	Generator.h -> klasa, generuj¹ca punkty w szeœcianie, w kuli oraz na powierzchni kuli
	GUI.cpp -> plik, w którym zachodzi wyœwietlanie punktów za pomoc¹ biblioteki OpenGL, wczytywane s¹ œciany a nastêpnie wyœwietlane jako trójk¹ty
	IncrementalHull.h -> klasa dziedzicz¹ca po ConvexHull i zawieraj¹ca metody odpowiedzialne za budowanie otoczki algorytmem przyrostowym
	Point.h -> klasa opisuj¹ca punkt w przestrzeni 3d
	QuickHull.h -> klasa dziedzicz¹ca po ConvexHull i zawieraj¹ca metody odpowiedzialne za budowanie otoczki algorytmem QuickHull
	Vertex.h -> klasa opakowuj¹ca klasê Point, opisuje wierzcho³ki trójk¹tów, buduj¹cych otoczkê