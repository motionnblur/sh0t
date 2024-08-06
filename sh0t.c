#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cairo/cairo.h>
#include <unistd.h>

int main(){
    Display *display;
    Window root;
    int screen;
    int width, height;
    XImage *image;
    unsigned char *data;
    FILE *fp;

    display = XOpenDisplay(NULL);
    if (!display) {
        fprintf(stderr, "Cannot open display\n");
        return 1;
    }
    
    // Get the root window
    screen = DefaultScreen(display);
    root = RootWindow(display, screen);

    // Get screen dimensions
    width = DisplayWidth(display, screen);
    height = DisplayHeight(display, screen);

    while(1){
        // Create an XImage
        image = XGetImage(display, root, 0, 0, width, height, AllPlanes, ZPixmap);
        if (!image) {
            fprintf(stderr, "Cannot get image\n");
            XCloseDisplay(display);
            return 1;
        }

        cairo_surface_t* surface = cairo_image_surface_create_for_data((unsigned char*)image->data, CAIRO_FORMAT_ARGB32, width, height, image->bytes_per_line);
        cairo_surface_write_to_png(surface, "screenshot.png");
        sleep(5);
    }
    // Create an XImage
    image = XGetImage(display, root, 0, 0, width, height, AllPlanes, ZPixmap);
    if (!image) {
        fprintf(stderr, "Cannot get image\n");
        XCloseDisplay(display);
        return 1;
    }

    cairo_surface_t* surface = cairo_image_surface_create_for_data((unsigned char*)image->data, CAIRO_FORMAT_ARGB32, width, height, image->bytes_per_line);
    cairo_surface_write_to_png(surface, "screenshot.png");

    cairo_surface_destroy(surface);
    XDestroyImage(image);
    XCloseDisplay(display);

    return 0;
}
