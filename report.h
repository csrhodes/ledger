#ifndef _REPORT_H
#define _REPORT_H

#include "session.h"
#include "valexpr.h"

#include <string>
#include <list>

namespace ledger {

class transform_t;
class repitem_t;

typedef std::list<std::string> strings_list;

class report_t : public valexpr_t::scope_t
{
 public:
  std::string output_file;
  std::string format_string;
  std::string amount_expr;
  std::string total_expr;
  std::string date_output_format;

  unsigned long budget_flags;

  std::string account;
  std::string pager;

  bool show_totals;
  bool keep_price;
  bool keep_date;
  bool keep_tag;

  session_t *   session;
  transform_t * last_transform;

  std::list<transform_t *> transforms;

  report_t(session_t * _session)
    : valexpr_t::scope_t(_session),

      show_totals(false),
      keep_price(false),
      keep_date(false),
      keep_tag(false),

      session(_session),

      last_transform(NULL) {
#if 0
    ledger::amount_expr = "@a";
    ledger::total_expr  = "@O";
#endif
  }
  virtual ~report_t();

  void apply_transforms(repitem_t * items);

  void regexps_to_predicate(const std::string& command,
			    std::list<std::string>::const_iterator begin,
			    std::list<std::string>::const_iterator end,
			    const bool account_regexp	       = false,
			    const bool add_account_short_masks = false,
			    const bool logical_and             = true);

  void process_options(const std::string&     command,
		       strings_list::iterator arg,
		       strings_list::iterator args_end);

#if 0
  item_handler<transaction_t> *
  chain_xact_handlers(const std::string& command,
		      item_handler<transaction_t> * base_formatter,
		      journal_t * journal,
		      account_t * master,
		      std::list<item_handler<transaction_t> *>& ptrs);
#endif

  //
  // Config options
  //

  void opt_foo(value_t& result) {
    std::cout << "This is foo" << std::endl;
  }
  void opt_bar(value_t& result, valexpr_t::scope_t * locals) {
    std::cout << "This is bar: " << locals->args[0] << std::endl;
  }

  //
  // Scope members
  //

  virtual valexpr_t::node_t * lookup(const std::string& name);
};

class balance_command : public valexpr_t::functor_t
{
 public:
  balance_command() : valexpr_t::functor_t("balance") {}

  virtual void operator()(value_t& result, valexpr_t::scope_t * args) {}
};

} // namespace ledger

#endif // _REPORT_H
