#include "link_get.h"

LinksGetter::LinksGetter()
    : html_(), link_(httputils::ProtocolType::HTTPS, "", ""), links_(),
      htmlTag_(R"(<a href="([^"]*))"),
      urlRegex_(R"((https?)://([^/]+)(/.*)?$)") {}

void LinksGetter::setHtml(const std::string html) {
  html_ = html;
  handleHtml();
}

void LinksGetter::setCurrentLink(const httputils::Link &link) { link_ = link; }

void LinksGetter::handleHtml() {
  std::smatch match;
  std::string::const_iterator searchStart(html_.cbegin());
  while (std::regex_search(searchStart, html_.cend(), match, htmlTag_)) {
    std::string protocol, hostName, path;
    std::string url = match[1].str();
    std::smatch urlMatch;

    if (std::regex_match(url, urlMatch, urlRegex_)) {
      if (urlMatch.size() == 4) {
        protocol = urlMatch[1].str();
        hostName = urlMatch[2].str();
        path = urlMatch[3].str();
      }
    } else {
      url = getProtocol(link_.protocol) + "://" + link_.hostName + link_.query +
            url;
      if (std::regex_match(url, urlMatch, urlRegex_)) {
        if (urlMatch.size() == 4) {
          protocol = urlMatch[1].str();
          hostName = urlMatch[2].str();
          path = urlMatch[3].str();
        }
      }
    }
    if (path.empty()) {
      path = "/";
    }

    httputils::Link link(httputils::setProtocolType(protocol), hostName, path);
    links_.push_back(link);
    searchStart = match.suffix().first;
  }
}

std::vector<httputils::Link> LinksGetter::getLinks() const { return links_; }

std::string LinksGetter::getURL() {
  const std::string URL =
      getProtocol(link_.protocol) + "://" + link_.hostName + link_.query;
  return URL;
}
