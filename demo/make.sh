cd /home/wiz/Downloads/gflags-2.2.2/build
sudo make uninstall
echo ">>>>> uninstall gflags over <<<<<"
cd /home/wiz/glog/
cmake --build build
sudo cmake --build build --target install
echo ">>>>> reinstall glog over <<<<<"
cd /home/wiz/Downloads/gflags-2.2.2/build
sudo make install
echo ">>>>> install gflags over <<<<<"
