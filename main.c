#include <X11/Xlib.h>
#include <X11/Xutil.h>

void raise_next_window (Display *dpy) {
	Window root, parent, *wins, *w;
	XWindowAttributes attr;
	unsigned int num_wins;
	
	/* Switch to the first viewable window we can find */
	XQueryTree(dpy, DefaultRootWindow(dpy),	&root, &parent,	&wins, &num_wins);
	for (w=wins; w < (wins+num_wins); w++) {
		XGetWindowAttributes(dpy, *w, &attr);
		if (attr.map_state == IsViewable) {
			XResizeWindow(dpy, *w,
				DisplayWidth(dpy, DefaultScreen(dpy)),
				DisplayHeight(dpy, DefaultScreen(dpy)));
			XRaiseWindow(dpy, *w);
			return;
		}
	}
}

int main() {
	Display *dpy;
	Window root;
	XEvent ev;

	if (!(dpy = XOpenDisplay(0))) return 1;       /* "Cannot open display" */
	root = DefaultRootWindow(dpy);	
	XGrabKey(dpy, XKeysymToKeycode(dpy, XStringToKeysym("Tab")), 
		Mod1Mask, root, True, GrabModeAsync, GrabModeAsync);

	for (;;) {
		XNextEvent(dpy, &ev);
		if (ev.type == KeyPress) raise_next_window (dpy);
	}		
}

