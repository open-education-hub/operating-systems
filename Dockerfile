FROM ghcr.io/open-education-hub/openedu_builder:0.3.1

# Install ffmpeg
RUN apt-get update && \
    apt-get install -y ffmpeg curl make

# Install markdown-pp
RUN pip install MarkdownPP

# Install node LTS (16)
RUN curl -fsSL https://deb.nodesource.com/setup_lts.x | bash - && \
    apt-get install -y nodejs

# Install reveal md
RUN npm install -g reveal-md

# Install docusaurus
RUN npm install create-docusaurus@2.1.0

WORKDIR /content

ENTRYPOINT ["oe_builder"]
