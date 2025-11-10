if [ $(id -u) -ne 0 ];
	then
		echo "This script must be executed as root or with sudo";
		exit 1;
fi

echo "Installation...";

cd $(dirname $0);
mkdir -p build;
cd build;
cmake ..;
make;
cp ./Tasker /usr/local/bin;
cd ../;

echo "Tasker has been installed successfully, restart your terminal.";

