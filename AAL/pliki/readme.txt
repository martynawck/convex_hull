-	Martyna Wi�cek 249481
- 	Problem do rozwi�zania polega� na znalezieniu pow�oki wypuk�ej dla zadanego zbior�w punkt�w w przestrzeni tr�jwymiarowej z zadan� dok�adno�ci�.
	Dok�adno�� jest opisywana przez dzia�anie funkcji Minimizer, kt�ra dla wygenerowanego zbioru punkt�w jest w stanie ograniczy� go metod� wokselizacji.
	Algorytmy zastosowane w programie to algorytm przyrostowy i QuickHull.
-	Dane wej�ciowe to w pierwszym wierszu wsp�rz�dne �rodka ci�ko�ci bry�y, na kt�rej opiera si� generacja punkt�w oraz w kolejnych liniach wsp�rz�dne x,y,z punktu.
	Prezentacja wynik�w odbywa si� za pomoc� wy�wietlenia powsta�ych �cian bry�y w OpenGl.
-	Algorytmami, kt�rych u�y�am do obliczenia otoczki wypuk�ej s� QuickHull oraz IncrementalHull. Przechowywane �ciany bry�y znajduj� si� w vectorze facets w klasie ConvexHull.
-	ConvexHull.h -> klasa, opisuj�ca obiekt otoczi wypuk�ej, znajduj� si� w niej �ciany bry�y oraz podstawowe metody
	Edge.h -> klasa opisuj�ca kraw�dz tr�jk�ta, kt�ry jest tworzony przy budowaniu otoczki.
	Facet.h -> klasa opisuj�ca �cian� otoczki czyli "tr�jk�t"
	Generator.h -> klasa, generuj�ca punkty w sze�cianie, w kuli oraz na powierzchni kuli
	GUI.cpp -> plik, w kt�rym zachodzi wy�wietlanie punkt�w za pomoc� biblioteki OpenGL, wczytywane s� �ciany a nast�pnie wy�wietlane jako tr�jk�ty
	IncrementalHull.h -> klasa dziedzicz�ca po ConvexHull i zawieraj�ca metody odpowiedzialne za budowanie otoczki algorytmem przyrostowym
	Point.h -> klasa opisuj�ca punkt w przestrzeni 3d
	QuickHull.h -> klasa dziedzicz�ca po ConvexHull i zawieraj�ca metody odpowiedzialne za budowanie otoczki algorytmem QuickHull
	Vertex.h -> klasa opakowuj�ca klas� Point, opisuje wierzcho�ki tr�jk�t�w, buduj�cych otoczk�