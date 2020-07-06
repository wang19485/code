# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.A5.Debug:
/Users/wangyingjian/desktop/main/A5/build/Debug/A5:
	/bin/rm -f /Users/wangyingjian/desktop/main/A5/build/Debug/A5


PostBuild.A5.Release:
/Users/wangyingjian/desktop/main/A5/build/Release/A5:
	/bin/rm -f /Users/wangyingjian/desktop/main/A5/build/Release/A5


PostBuild.A5.MinSizeRel:
/Users/wangyingjian/desktop/main/A5/build/MinSizeRel/A5:
	/bin/rm -f /Users/wangyingjian/desktop/main/A5/build/MinSizeRel/A5


PostBuild.A5.RelWithDebInfo:
/Users/wangyingjian/desktop/main/A5/build/RelWithDebInfo/A5:
	/bin/rm -f /Users/wangyingjian/desktop/main/A5/build/RelWithDebInfo/A5




# For each target create a dummy ruleso the target does not have to exist
