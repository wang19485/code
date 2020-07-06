# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.A1.Debug:
/Users/wangyingjian/desktop/main/A1/build/Debug/A1:
	/bin/rm -f /Users/wangyingjian/desktop/main/A1/build/Debug/A1


PostBuild.A1.Release:
/Users/wangyingjian/desktop/main/A1/build/Release/A1:
	/bin/rm -f /Users/wangyingjian/desktop/main/A1/build/Release/A1


PostBuild.A1.MinSizeRel:
/Users/wangyingjian/desktop/main/A1/build/MinSizeRel/A1:
	/bin/rm -f /Users/wangyingjian/desktop/main/A1/build/MinSizeRel/A1


PostBuild.A1.RelWithDebInfo:
/Users/wangyingjian/desktop/main/A1/build/RelWithDebInfo/A1:
	/bin/rm -f /Users/wangyingjian/desktop/main/A1/build/RelWithDebInfo/A1




# For each target create a dummy ruleso the target does not have to exist
