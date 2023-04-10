#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause

APP_NAME="app-schedule-threads"
LIBS="musl"
TOP="workdir"

UK="$TOP/unikraft"
APP="$TOP/apps/$APP_NAME"

KVM_IMAGE_NOCOOP="$APP_NAME-nocoop_kvm-x86_64"
KVM_IMAGE_COOP="$APP_NAME-coop_kvm-x86_64"
APP_BIN_NOCOOP="$APP/build/$KVM_IMAGE_NOCOOP"
APP_BIN_COOP="$APP/build/$KVM_IMAGE_COOP"

ARGUMENTS="-nographic -nodefaults "
ARGUMENTS+="-display none -serial stdio "

usage()
{
	echo "Usage: $0 <command>" 1>&2
	echo "  command: setup build run_coop run_nocoop clean remove" 1>&2
}

setup_app()
{
	sudo apt install -y --no-install-recommends \
		build-essential \
		libncurses-dev \
		libyaml-dev \
		flex \
		git \
		wget \
		socat \
		bison \
		unzip \
		uuid-runtime \
		qemu-system-x86

	if ! test -d "$UK"; then
		git clone https://github.com/unikraft/unikraft "$UK"

		pushd "$UK" > /dev/null || exit 1
		git fetch --all --tags
		git checkout "RELEASE-0.12.0"
		popd > /dev/null || exit 1
	fi

	mkdir "$TOP/libs/" 2> /dev/null
	pushd "$TOP/libs/" > /dev/null || exit 1
	for lib in $LIBS; do
		test -d "$lib" || git clone https://github.com/unikraft/lib-"$lib" "$lib"

		pushd "$lib" > /dev/null || exit 1
		git fetch --all --tags
		git checkout "RELEASE-0.12.0"
		popd > /dev/null || exit 1
	done
	popd > /dev/null || exit 1
}

build_nocoop_app()
{
	pushd "$APP" > /dev/null || exit 1
	UK_WORKDIR=$(pwd)/../../ make C="$(pwd)/.config_nocoop" prepare < /dev/null
	UK_WORKDIR=$(pwd)/../../ make C="$(pwd)/.config_nocoop" -j"$(ncpus)" < /dev/null
	popd > /dev/null || exit 1
}

build_coop_app()
{
	pushd "$APP" > /dev/null || exit 1
	UK_WORKDIR=$(pwd)/../../ make C="$(pwd)/.config_coop" prepare < /dev/null
	UK_WORKDIR=$(pwd)/../../ make C="$(pwd)/.config_coop" -j"$(ncpus)" < /dev/null
	popd > /dev/null || exit 1
}

run_app_coop()
{
	ARGUMENTS+="-kernel $APP_BIN_COOP"
	if ! test -f "$APP_BIN_COOP"; then
		echo "$APP_BIN_COOP does not exists. Did you run ./do.sh setup; ./do.sh build ?"
		exit 1
	fi

	eval qemu-system-x86_64 "$ARGUMENTS"
}

run_app_nocoop()
{
	ARGUMENTS+="-kernel $APP_BIN_NOCOOP"
	if ! test -f "$APP_BIN_NOCOOP"; then
		echo "$APP_BIN_NOCOOP does not exists. Did you run ./do.sh setup; ./do.sh build ?"
		exit 1
	fi

	eval qemu-system-x86_64 "$ARGUMENTS"
}

clean_app()
{
	pushd "$APP" > /dev/null || exit 1
	UK_WORKDIR=$(pwd)/../../ make C="$(pwd)/.config_coop" properclean
	popd > /dev/null || exit 1
}

clean_all()
{
	clean_app
	if test -d "$UK"; then
		rm -rf "$UK" 2> /dev/null
	fi

	pushd "$TOP/libs/" > /dev/null || exit 1
	for lib in $LIBS; do
		test -d "$lib" && rm -rf "$lib" 2> /dev/null
	done
}

command="$1"
unset UK_WORKDIR
unset UK_ROOT
unset UK_LIBS

case "$command" in

	"setup")
		setup_app
		;;

	"build")
		build_coop_app

		# HACK:
		# To avoid doing a properclean that will take a long time,
		# just remove the files that set the
		# `CONFIG_APPSCHEDULETHREADS_COOPERATE` config option
		pushd "$APP/build/" > /dev/null || exit 1
		rm -r include/ config appschedulethreads*
		popd > /dev/null || exit 1

		build_nocoop_app
		;;

	"run_coop")
		run_app_coop
		;;

	"run_nocoop")
		run_app_nocoop
		;;

	"clean")
		clean_app
		;;

	"remove")
		clean_all
		;;

	*)
		usage
		exit 1

esac
