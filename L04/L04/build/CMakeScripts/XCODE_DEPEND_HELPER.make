# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.L04.Debug:
PostBuild.glfw.Debug: /Users/wangyingjian/desktop/main/L04/L04/build/Debug/L04
/Users/wangyingjian/desktop/main/L04/L04/build/Debug/L04:\
	/Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/Debug/libglfw3.a\
	/Users/wangyingjian/desktop/main/lib/csce441/glew-2.1.0/lib/libGLEW.a
	/bin/rm -f /Users/wangyingjian/desktop/main/L04/L04/build/Debug/L04


PostBuild.glfw.Debug:
/Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/Debug/libglfw3.a:
	/bin/rm -f /Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/Debug/libglfw3.a


PostBuild.L04.Release:
PostBuild.glfw.Release: /Users/wangyingjian/desktop/main/L04/L04/build/Release/L04
/Users/wangyingjian/desktop/main/L04/L04/build/Release/L04:\
	/Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/Release/libglfw3.a\
	/Users/wangyingjian/desktop/main/lib/csce441/glew-2.1.0/lib/libGLEW.a
	/bin/rm -f /Users/wangyingjian/desktop/main/L04/L04/build/Release/L04


PostBuild.glfw.Release:
/Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/Release/libglfw3.a:
	/bin/rm -f /Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/Release/libglfw3.a


PostBuild.L04.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/wangyingjian/desktop/main/L04/L04/build/MinSizeRel/L04
/Users/wangyingjian/desktop/main/L04/L04/build/MinSizeRel/L04:\
	/Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/MinSizeRel/libglfw3.a\
	/Users/wangyingjian/desktop/main/lib/csce441/glew-2.1.0/lib/libGLEW.a
	/bin/rm -f /Users/wangyingjian/desktop/main/L04/L04/build/MinSizeRel/L04


PostBuild.glfw.MinSizeRel:
/Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/MinSizeRel/libglfw3.a:
	/bin/rm -f /Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/MinSizeRel/libglfw3.a


PostBuild.L04.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/wangyingjian/desktop/main/L04/L04/build/RelWithDebInfo/L04
/Users/wangyingjian/desktop/main/L04/L04/build/RelWithDebInfo/L04:\
	/Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/RelWithDebInfo/libglfw3.a\
	/Users/wangyingjian/desktop/main/lib/csce441/glew-2.1.0/lib/libGLEW.a
	/bin/rm -f /Users/wangyingjian/desktop/main/L04/L04/build/RelWithDebInfo/L04


PostBuild.glfw.RelWithDebInfo:
/Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/RelWithDebInfo/libglfw3.a:
	/bin/rm -f /Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/RelWithDebInfo/libglfw3.a




# For each target create a dummy ruleso the target does not have to exist
/Users/wangyingjian/desktop/main/lib/csce441/glew-2.1.0/lib/libGLEW.a:
/Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/Debug/libglfw3.a:
/Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/MinSizeRel/libglfw3.a:
/Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/RelWithDebInfo/libglfw3.a:
/Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/src/Release/libglfw3.a:
