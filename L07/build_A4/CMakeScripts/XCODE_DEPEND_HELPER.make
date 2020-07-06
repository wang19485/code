# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.A3.Debug:
PostBuild.glfw.Debug: /Users/wangyingjian/desktop/main/L07/build/Debug/A3
/Users/wangyingjian/desktop/main/L07/build/Debug/A3:\
	/Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/Debug/libglfw3.a\
	/Users/wangyingjian/desktop/main/lib/csce441/glew-2.1.0/lib/libGLEW.a
	/bin/rm -f /Users/wangyingjian/desktop/main/L07/build/Debug/A3


PostBuild.glfw.Debug:
/Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/Debug/libglfw3.a:
	/bin/rm -f /Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/Debug/libglfw3.a


PostBuild.A3.Release:
PostBuild.glfw.Release: /Users/wangyingjian/desktop/main/L07/build/Release/A3
/Users/wangyingjian/desktop/main/L07/build/Release/A3:\
	/Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/Release/libglfw3.a\
	/Users/wangyingjian/desktop/main/lib/csce441/glew-2.1.0/lib/libGLEW.a
	/bin/rm -f /Users/wangyingjian/desktop/main/L07/build/Release/A3


PostBuild.glfw.Release:
/Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/Release/libglfw3.a:
	/bin/rm -f /Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/Release/libglfw3.a


PostBuild.A3.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/wangyingjian/desktop/main/L07/build/MinSizeRel/A3
/Users/wangyingjian/desktop/main/L07/build/MinSizeRel/A3:\
	/Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/MinSizeRel/libglfw3.a\
	/Users/wangyingjian/desktop/main/lib/csce441/glew-2.1.0/lib/libGLEW.a
	/bin/rm -f /Users/wangyingjian/desktop/main/L07/build/MinSizeRel/A3


PostBuild.glfw.MinSizeRel:
/Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/MinSizeRel/libglfw3.a:
	/bin/rm -f /Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/MinSizeRel/libglfw3.a


PostBuild.A3.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/wangyingjian/desktop/main/L07/build/RelWithDebInfo/A3
/Users/wangyingjian/desktop/main/L07/build/RelWithDebInfo/A3:\
	/Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/RelWithDebInfo/libglfw3.a\
	/Users/wangyingjian/desktop/main/lib/csce441/glew-2.1.0/lib/libGLEW.a
	/bin/rm -f /Users/wangyingjian/desktop/main/L07/build/RelWithDebInfo/A3


PostBuild.glfw.RelWithDebInfo:
/Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/RelWithDebInfo/libglfw3.a:
	/bin/rm -f /Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/RelWithDebInfo/libglfw3.a




# For each target create a dummy ruleso the target does not have to exist
/Users/wangyingjian/desktop/main/lib/csce441/glew-2.1.0/lib/libGLEW.a:
/Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/Debug/libglfw3.a:
/Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/MinSizeRel/libglfw3.a:
/Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/RelWithDebInfo/libglfw3.a:
/Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/Release/libglfw3.a:
