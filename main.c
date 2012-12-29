#include <X11/Xlib.h>
#include <X11/Xutil.h>

void raise_next_window (Display *dpy) {
	Window root, parent, *wins, *w;
	unsigned int num_wins;
	XQueryTree(dpy, 
		DefaultRootWindow(dpy), 
		&root, 
		&parent, 
		&wins, 
		&num_wins);

	/* Switch to the first viewable window we can find, *
	 *  back-to-front (I guess).                        */
	for (w=wins; w<wins+num_wins; w++) {
		XWindowAttributes attr;
		XGetWindowAttributes(dpy,*w,&attr);
		if (attr.map_state == IsViewable) {
			XRaiseWindow(dpy,*w);
			return;
		}
	}
}

int main() {
	Display *dpy;
	Window root;
	XEvent ev;

	dpy = XOpenDisplay(0);
	if (!dpy) return 1; /* "Cannot open display" */

	/* Default screen only. Multi-head may be out of luck. */
	root = DefaultRootWindow(dpy);
	
	XGrabKey(dpy,
		XKeysymToKeycode(dpy, XStringToKeysym("Tab")),
		Mod1Mask,
		root,
		True,
		GrabModeAsync,
		GrabModeAsync);

	/* Basic main loop */
	for (;;) {
		XNextEvent(dpy, &ev);
		if (ev.type == KeyPress) {
			raise_next_window (dpy);
		}
	}		
}

