FROM ubuntu:20.04 AS build-env

RUN DEBIAN_FRONTEND=noninteractive apt-get update \
    && apt-get install -y --no-install-recommends \
        build-essential \
        git \
        autoconf \
        automake \
        libtool \
        libssl-dev \
        liblivemedia-dev \
        libjson-c-dev \
        pkg-config \
        ruby \
    && apt-get clean \
    && rm -rf /var/lib/apt

RUN gem install fpm

WORKDIR /videop2proxy/
COPY ./ /videop2proxy/src/
RUN cd src \
    ; ./autogen.sh \
    && make \
    && mkdir -p /videop2proxy/tmp \
    && make DESTDIR=/videop2proxy/tmp install \
    && cd .. \
    ; fpm -s dir -t deb \
        -C /videop2proxy/tmp \
        --name videop2proxy \
        --version 0.0.1 \
        --iteration 1 \
        --depends liblivemedia77 \
        --depends libjson-c4 \
        --description "Proxy to enable P2P only cameras to work with RTSP protocol" \
        .

FROM ubuntu:20.04 AS run-env

RUN DEBIAN_FRONTEND=noninteractive apt-get update \
    && apt-get install -y liblivemedia77 libjson-c4 \
    && apt-get clean \
    && rm -rf /var/lib/apt

COPY --from=build-env /videop2proxy/videop2proxy_0.0.1-1_amd64.deb /tmp
RUN dpkg -i /tmp/videop2proxy_0.0.1-1_amd64.deb

ENTRYPOINT [ "videop2proxy", "--rtsp-port", "554", "--cam-login", "admin" ]
CMD [ "--cam-pass", "000000" ]
EXPOSE 554/tcp