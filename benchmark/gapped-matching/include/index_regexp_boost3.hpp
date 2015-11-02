#pragma once

#include "utils.hpp"
#include "collection.hpp"
#include "sdsl/int_vector.hpp"

#include <boost/regex.hpp>

class index_regexp_boost3
{
    public:
        typedef sdsl::int_vector<0>::size_type size_type;
        typedef sdsl::int_vector<0>::value_type value_type;
        typedef std::string text_type;
        std::string name() const
        {
            std::string index_name = IDXNAME;
            return "REGEXP-BOOST-"+index_name;
        }
    protected:
        boost::regex rx;
        text_type m_text;
    public:
        index_regexp_boost3() { }
        index_regexp_boost3(collection& col)
        {
            sdsl::int_vector_mapper<0> sdsl_text(col.file_map[consts::KEY_TEXT]);
            std::copy(sdsl_text.begin(),sdsl_text.end(),std::back_inserter(m_text));
        }

        size_type serialize(std::ostream& ofs, sdsl::structure_tree_node* v=NULL, std::string name="")const
        {
            (void)v;
            (void)name;
            ofs << m_text;
            return m_text.size();
        }

        void load(std::istream& ifs)
        {
            m_text = text_type(std::istreambuf_iterator<char>(ifs), {});
        }

        void swap(index_regexp_boost3& ir)
        {
            if (this != &ir) {
                m_text.swap(ir.m_text);
            }
        }

        std::string info(const gapped_pattern& pat) const { (void)pat; return ""; }

        void prepare(const gapped_pattern& pat)
        {
            /* (1) construct regexp */
            rx = boost::regex(pat.raw_regexp.begin(),pat.raw_regexp.end(),REGEXP_TYPE);
        }

        //! Search for the k documents which contain the search term most frequent
        gapped_search_result
        search(const gapped_pattern& pat) const
        {
            (void)pat;

            /* (2) find all matching pos */
            auto matches_begin = boost::sregex_iterator(m_text.begin(),m_text.end(),rx,boost::regex_constants::match_flag_type::match_not_dot_newline);
            auto matches_end = boost::sregex_iterator();


            /* (3) copy the output */
            gapped_search_result res;
            for (boost::sregex_iterator it = matches_begin; it != matches_end; ++it) {
                res.positions.push_back(it->position());
            }
            return res;
        }
};
