# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.L01.Debug:
/Users/wangyingjian/desktop/main/L01/build/Debug/L01:
	/bin/rm -f /Users/wangyingjian/desktop/main/L01/build/Debug/L01


PostBuild.L01.Release:
/Users/wangyingjian/desktop/main/L01/build/Release/L01:
	/bin/rm -f /Users/wangyingjian/desktop/main/L01/build/Release/L01


PostBuild.L01.MinSizeRel:
/Users/wangyingjian/desktop/main/L01/build/MinSizeRel/L01:
	/bin/rm -f /Users/wangyingjian/desktop/main/L01/build/MinSizeRel/L01


PostBuild.L01.RelWithDebInfo:
/Users/wangyingjian/desktop/main/L01/build/RelWithDebInfo/L01:
	/bin/rm -f /Users/wangyingjian/desktop/main/L01/build/RelWithDebInfo/L01




# For each target create a dummy ruleso the target does not have to exist
