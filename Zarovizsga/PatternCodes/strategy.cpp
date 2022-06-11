#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

enum class Format { Markdown, Html };

struct ListStrategy {
	virtual ~ListStrategy() = default;

	virtual void item(std::ostringstream&, const std::string&) = 0;
	virtual void start(std::ostringstream&) {}
	virtual void stop(std::ostringstream&) {}
};

struct MarkdownList : public ListStrategy {
	void item(std::ostringstream &out, const std::string &item) final {
		out << " - " << item << '\n';
	}
};

struct HtmlList : public ListStrategy {
	void item(std::ostringstream &out, const std::string &item) final {
		out << "  <li>" << item << "</li>\n";
	}

	void start(std::ostringstream &out) final {
		out << "<ul>\n";
	}

	void stop(std::ostringstream &out) final {
		out << "</ul>\n";
	}
};

struct TextProcessor {

private:

	std::ostringstream out;
	std::unique_ptr<ListStrategy> strategy;


public:

	void setFormat(Format format) {
		switch (format) {
		case Format::Markdown:
			strategy = std::make_unique<MarkdownList>();
			break;
		case Format::Html:
			strategy = std::make_unique<HtmlList>();
			break;
		}
	}

	std::string str() { return out.str(); }

	void clear() {
		out.str("");
		out.clear();
	}

	void setList(const std::vector<std::string> &items) {
		strategy->start(out);
		for (const auto &x : items)
			strategy->item(out, x);
		strategy->stop(out);
	}
};


int main() {

	TextProcessor tp;

	tp.setFormat(Format::Markdown);
	tp.setList({"foo", "bar", "baz"});
	std::cout << tp.str() << '\n';


	tp.clear();
	tp.setFormat(Format::Html);
	tp.setList({ "foo", "bar", "baz" });
	std::cout << tp.str() << '\n';
}
