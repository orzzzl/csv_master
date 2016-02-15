#include "csv_master.h"

csv_master::csv_master(const string &file_name, string &out_file_name, bool has_header_) {
  // if output file is not specified, then it will be "csv_master.out"
  if (out_file_name.empty()) {
    out_file_name = "csv_master.out";
  }
  has_header = has_header_;
  line_num = 0;
  ifstream in_file(file_name);
  assert(access(file_name.c_str(), F_OK) != -1);
  fout = ofstream(out_file_name);
  string line;
  recs.clear();
  bool initial = true;
  while (getline(in_file, line)) {
    if (initial) {
      initial_setup(line);
      initial = false;
      if (has_header) continue;
    }
    record tmp(line_num++);
    tmp.input_line(line, stats_of_cols);
    recs.push_back(tmp);
  }
}

void csv_master::initial_setup(const string &line) {
  num_of_cols = 1;
  stats_of_cols.push_back(stats());
  string buf;
  for (auto ele : line) {
    if (ele == ',') {
      if (has_header) {
        header_names.push_back(buf);
        buf.clear();
      } else {
        header_names.push_back(to_string(num_of_cols - 1));
      }
      num_of_cols++;
      stats_of_cols.push_back(stats());
    } else {
      buf.push_back(ele);
    }
  }
  if (has_header) {
    header_names.push_back(buf);
  } else {
    header_names.push_back(to_string(num_of_cols - 1));
  }
}

void csv_master::print_all(const set<int> &st) {
  fout << "line";
  for (int i = 0; i < header_names.size(); i++) 
    if (st.empty() || st.find(i) != st.end()) 
      fout << setw(5) << header_names[i] << "  ";
  fout << endl;
  for (auto i : recs) {
    i.report(st, fout);
  }
}


void csv_master::create_col(int col1, int col2, char op) {
  for (auto &rc : recs) {
    rc.add_col(col1, col2, op);
  }
}

void csv_master::show_stats(int col_no) {
  if (col_no < 0 || col_no >= stats_of_cols.size()) {
    cout << "col number out of bound\n";
  } else {
    stats_of_cols[col_no].show(col_no);
  }
  while (recs[0].content.size() > header_names.size()) header_names.push_back("new");  
}



void csv_master::add_new_records(const csv_master &other, int col_no) {
  set<string> st;
  for (auto i : recs) {
    assert(col_no >= 0 and col_no < i.content.size());
    st.insert(i.content[col_no]);
  }
  for (auto i : other.recs) {
    if (st.find(i.content[col_no]) == st.end()) {
      record tmp(line_num++);
      for (int k = 0; k < num_of_cols; k++) {
        if (k != col_no) {
          string str_tmp = "";
          tmp.input_word(str_tmp);
        } else {
          tmp.input_word(i.content[col_no]);
        }
      }
      for (int k = 0; k < i.content.size(); k++) {
        if (k == col_no) continue;
        tmp.input_word(i.content[k]);
      }
      recs.push_back(tmp);
    }
  }
}

void csv_master::join(const csv_master &other, bool outer, int col_no) {
  map<string, record> exist;
  for (auto i : other.recs) {
    assert(col_no >= 0 and col_no < i.content.size());
    exist[i.content[col_no]] = i;
  }
  for (int i = 0; i < recs.size(); ) {
    assert(col_no >= 0 and col_no < recs[i].content.size());
    if (exist.find(recs[i].content[col_no]) == exist.end()) {
      // not found 
      if (outer) {
        i++;
      } else {
        recs.erase(recs.begin() + i);
      }
    } else {
      for (auto ele : exist[recs[i].content[col_no]].content) {
        if (recs[i].content[col_no] == ele) continue;
        recs[i].input_word(ele);
      }
      i++;
    }
  }
  if (outer) add_new_records(other, col_no);
  // merge stats for columes
  for (int k = 0; k < other.stats_of_cols.size(); k++) {
    if (col_no == k) continue;
    stats_of_cols.push_back(other.stats_of_cols[k]);
  }
  while (recs[0].content.size() > header_names.size()) header_names.push_back("new");
}
