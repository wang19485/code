#include <iostream>
#include <string>
#include<time.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "Image.h"

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;

int main(int argc, char **argv)
{
	if(argc < 2) {
		cout << "Usage: A1 meshfile" << endl;
		return 0;
	}
    srand(time(0));
	string meshName(argv[1]);

	// Load geometry
	vector<float> posBuf; // list of vertex positions
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	string errStr;
    float minx = INFINITY;
    float miny = INFINITY;
    float maxx = -INFINITY;
    float maxy = -INFINITY;
    float minz = INFINITY;
    float maxz = -INFINITY;
	bool rc = tinyobj::LoadObj(&attrib, &shapes, &materials, &errStr, meshName.c_str());
	if(!rc) {
		cerr << errStr << endl;
	} else {
		// Some OBJ files have different indices for vertex positions, normals,
		// and texture coordinates. For example, a cube corner vertex may have
		// three different normals. Here, we are going to duplicate all such
		// vertices.
		// Loop over shapes
        
		for(size_t s = 0; s < shapes.size(); s++) {
			// Loop over faces (polygons)
			size_t index_offset = 0;
			for(size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				size_t fv = shapes[s].mesh.num_face_vertices[f];
				// Loop over vertices in the face.
				for(size_t v = 0; v < fv; v++) {
					// access to vertex
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
					posBuf.push_back(attrib.vertices[3*idx.vertex_index+0]);
					posBuf.push_back(attrib.vertices[3*idx.vertex_index+1]);
					posBuf.push_back(attrib.vertices[3*idx.vertex_index+2]);
                    
                    if (attrib.vertices[3*idx.vertex_index+0] < minx) {
                        minx = attrib.vertices[3*idx.vertex_index+0];
                    }
                    if (attrib.vertices[3*idx.vertex_index+1] < miny) {
                        miny = attrib.vertices[3*idx.vertex_index+1];
                    }
                    if (attrib.vertices[3*idx.vertex_index+0] > maxx) {
                        maxx = attrib.vertices[3*idx.vertex_index+0];
                    }
                    if (attrib.vertices[3*idx.vertex_index+1] > maxy) {
                        maxy = attrib.vertices[3*idx.vertex_index+1];
                    }
                    if (attrib.vertices[3*idx.vertex_index+2] < minz) {
                        minz = attrib.vertices[3*idx.vertex_index+2];
                    }
                    if (attrib.vertices[3*idx.vertex_index+2] > maxz) {
                        maxz = attrib.vertices[3*idx.vertex_index+2];
                    }
				}
				index_offset += fv;
				// per-face material (IGNORE)
				shapes[s].mesh.material_ids[f];
			}
		}
        cout << miny << maxy;
	}
    int mode = atoi(argv[5]);
    float width = stof(argv[3]);
    float height = stof(argv[4]);
	cout << "Number of vertices: " << posBuf.size()/3 << endl;
    
    float s1 = height/(maxy - miny);
    float s2 = width/(maxx - minx);
    float s = 0;
    if (s1 > s2) {
        s = s2;
    }else{
        s = s1;
    }
    float tx = width/2 - s*(minx + maxx)/2;
    float ty = height/2 - s*(miny + maxy)/2;
    auto image = make_shared<Image>(width, height);
    auto image2 = make_shared<Image>(width, height);
    auto image3 = make_shared<Image>(width, height);
    auto image4 = make_shared<Image>(width, height);
    auto image5 = make_shared<Image>(width, height);
    auto image6 = make_shared<Image>(width, height);
    
    unsigned char r = 255;
    unsigned char g = 255;
    unsigned char b = 255;
    
    vector<vector<float>> zbuffer(height,vector<float> (width,-INFINITY));
    for (int i = 0; i < posBuf.size(); i+=9) {
        vector<float>x;
        x.push_back(posBuf[i]);
        x.push_back(posBuf[i+3]);
        x.push_back(posBuf[i+6]);
        vector<float>y;
        y.push_back(posBuf[i+1]);
        y.push_back(posBuf[i+4]);
        y.push_back(posBuf[i+7]);
        
        int x0 = x[0]*s + tx;
        int x1 = x[1]*s + tx;
        int x2 = x[2]*s + tx;
        int y0 = y[0]*s + ty;
        int y1 = y[1]*s + ty;
        int y2 = y[2]*s + ty;
        
        float z0 = posBuf[i+2];
        float z1 = posBuf[i+5];
        float z2 = posBuf[i+8];
        
        // random color for 3 vertices
        unsigned char r1 = rand()%256;
        unsigned char g1 = rand()%256;
        unsigned char b1 = rand()%256;
        
        unsigned char r2 = rand()%256;
        unsigned char g2 = rand()%256;
        unsigned char b2 = rand()%256;
        
        unsigned char r3 = rand()%256;
        unsigned char g3 = rand()%256;
        unsigned char b3 = rand()%256;
        
        for (int j = *min_element(y.begin(),y.end())*s+ty; j <= *max_element(y.begin(),y.end())*s+ty; j++) {
            for (int k = *min_element(x.begin(),x.end())*s+tx; k <= *max_element(x.begin(),x.end())*s+tx; k++) {
                if (j < height && k < width) {
                    image->setPixel(k, j, r1, g1, b1); // Drawing bounding box
                    
                    //Total area
                    float totalarea = 0.5*((x1-x0)*(y2-y0)-(x2-x0)*(y1-y0));
                    //PAB
                    float pab = 0.5*((x0-k)*(y1-j)-(x1-k)*(y0-j));
                    //PBC
                    float pbc = 0.5*((x1-k)*(y2-j)-(x2-k)*(y1-j));
                    //PCA
                    float pca = 0.5*((x2-k)*(y0-j)-(x0-k)*(y2-j));
                    if (totalarea > 0) {
                        if (pab/totalarea >= 0 && pab/totalarea <= 1) {
                            if (pbc/totalarea >= 0 && pbc/totalarea <= 1) {
                                if (pca/totalarea >= 0 && pca/totalarea <= 1) {
                                    image2->setPixel(k, j, r1, g1, b1); // Drawing Triangles
                                    float z = (pab/totalarea)*z2 + (pbc/totalarea)*z0 + (pca/totalarea)*z1;
                                    
                                    //calculate rbg based on barycentric coordinates
                                    r = (pab/totalarea) * (r3) + (pbc/totalarea) * r1 + (pca/totalarea) * r2;
                                    g = (pab/totalarea) * (g3) + (pbc/totalarea) * g1 + (pca/totalarea) * g2;
                                    b = (pab/totalarea) * (b3) + (pbc/totalarea) * b1 + (pca/totalarea) * b2;
                                    
                                    if (z >= zbuffer[j][k]) {
                                        image4->setPixel(k, j, r, g, b); // After adding Z-buffering
                                        zbuffer[j][k] = z;
                                    }
                                    if (mode == 0) {
                                        image3->setPixel(k, j, r, g, b); // mode 0
                                    }
                                    if (mode == 1) {
                                        // Red is chooese in this case
                                        if (z >= zbuffer[j][k]) {
                                            zbuffer[j][k] = z;
                                            r = 255 * (z-minz)/(maxz-minz);
                                            image5->setPixel(k, j, r, 0, 0); // mode 1
                                        }
                                    }
                                    if (mode == 2) {
                                        // calculate pixel color based on top-color and bottom color
                                        // In this case, top-color is cyan (0,255,255),
                                        // and the bottom-color is yellow (255,255,0).
                                        unsigned char rtop = j/height * 0;
                                        unsigned char gtop = j/height * 255;
                                        unsigned char btop = j/height * 255;
                                        unsigned char rbot = (height-j)/height * 255;
                                        unsigned char gbot = (height-j)/height * 255;
                                        unsigned char bbot = (height-j)/height * 0;
                                        r = rtop + rbot;
                                        g = gtop + gbot;
                                        b = btop + bbot;
                                        image6->setPixel(k, j, r, g, b);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
	image->writeToFile(argv[2]);
    image2->writeToFile("triangle.png");
    if (mode == 0) {
        image3->writeToFile("mode0.png");
    }
    image4->writeToFile("z_buffing.png");
    if (mode == 1) {
        image5->writeToFile("mode1.png");
    }
    if (mode == 2) {
        image6->writeToFile("mode2.png");
    }
    
	return 0;
}
