//
//

class DisplayList {
public:
  DisplayList( Paint pp, int width, int height);
  ~DisplayList();
  void DrawFromList( int npoint, int* xpoints, int* ypoints, byte* movedraw, int x0, int y0, int colored);
  void DrawClipped( int x0, int y0, int x1, int y1, int xmin, int xmax, int ymin, int ymax, int colored);
  int  GetWidth(void);
  void SetWidth(int width);
  int  GetHeight(void);
  void SetHeight(int height);
private:
  Paint* paint;
  int width;
  int height;
}
