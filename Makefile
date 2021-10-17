SHELL=/bin/bash

clear:
	-find ./intel_386/outputs/ -name "*.o*" -exec rm {} \;
	-find . -name "*.exe" -exec rm --force {} \;
	# -find . -name "*.pdb" -exec rm --force {} \;
	-find . -name ".gdb_history" -exec rm --force {} \;
	-find . -name ".bash_history" -exec rm --force {} \;
	-find . -name ".cache" -exec rm --force {} \;
	-find . -name "peda-session-*" -exec rm --force {} \;
	-find . -name ".python_history-*" -exec rm --force {} \;


day := `date +"%Y_%m_%d"`
m := autopush ${day}
branch := origin master
autopush: ## This is auto push module, need commit message(default=autopush)
	git add .
	git commit -m "${m}"
	git push ${branch}

pull:
	git pull ${branch}

force_pull:
	git fetch ${branch}
	git reset --hard origin/master

cache_clear:
	git rm -r --cached .

start_docker:
	sudo /etc/init.d/docker start

login_container:
	docker run --rm -it -v `pwd`/src:/try2windbg kashiwabayuki/try2windbg:1.0 bash -c "cd /try2windbg && bash"

# 作成した EXE と PDB ファイルを配置するパスを指定
PUTDIR := /mnt/d/Transfer
move:
	-find ./src/ -name "*.exe" -exec cp {} ${PUTDIR} \;
	-find ./src/ -name "*.exe" -exec mv {} ./bin --force \;
	-find ./src/ -name "*.pdb" -exec cp {} ${PUTDIR} \;
	-find ./src/ -name "*.pdb" -exec mv {} ./symbol --force \;

compile:
	docker run --rm -it -v `pwd`/src:/try2windbg kashiwabayuki/try2windbg:1.0 bash -c "cd /try2windbg && make"

run:
	make compile
	make move
