.PHONY: build
    
build:
	cd builddir && time ninja && time ninja test

clean:
	rm -fr builddir
	meson builddir

