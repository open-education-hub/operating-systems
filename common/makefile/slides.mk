RVMD = reveal-md
MDPP = markdown-pp
FFMPEG = ffmpeg

SLIDES ?= slides.mdpp
SLIDES_OUT ?= slides.md
MEDIA_DIR ?= media
SITE ?= _site
OPEN ?= xdg-open

.PHONY: all html clean videos

all: videos html

html: $(SITE)

$(SITE): $(SLIDES)
	$(MDPP) $< -o $(SLIDES_OUT)
	$(RVMD) $(SLIDES_OUT) --static $@

videos:
	for TARGET in $(TARGETS); do \
		$(FFMPEG) -framerate 0.5 -f image2 -y \
			-i "$(MEDIA_DIR)/$$TARGET/$$TARGET-%d.svg" -vf format=yuv420p $(MEDIA_DIR)/$$TARGET-generated.gif; \
	done

open: $(SITE)
	$(OPEN) $</index.html

clean:
	-rm -f $(MEDIA_DIR)/*-generated.gif
	-rm -f *~
	-rm -fr $(SITE) $(SLIDES_OUT)
