

/*     Type definitions of OMnet records.		*/
/*     Version 4.1-1325					*/
/*     Created  Wed Oct 21 15:24:49 2020		*/

/*     Definitions of sub structures			*/


#ifndef __OMEX_SGX_H
#define __OMEX_SGX_H
#if !(defined(INTLIST) && defined(QUADWORDS))
typedef   struct { char quad_word[8]; } quad_word;
#else
#define quad_word quadword
#endif


#include "om_inttypes.h"
#include "oal_align_packed.h"

typedef struct transaction_type
{
   char central_module_c;
   char server_type_c;
   uint16_t transaction_number_n;
} transaction_type_t;


/*   NAMED STRUCT = 50000  */

typedef struct series
{
   uint8_t country_c;
   uint8_t market_c;
   uint8_t instrument_group_c;
   uint8_t modifier_c;
   uint16_t commodity_n;
   uint16_t expiration_date_n;
   int32_t strike_price_i;
} series_t;


typedef struct account
{
   char country_id_s [2];
   char ex_customer_s [5];
   char account_id_s [16];
   char filler_1_s;
} account_t;


typedef struct countersign
{
   char country_id_s [2];
   char ex_customer_s [5];
   char filler_1_s;
} countersign_t;


typedef struct prop_trade_account
{
   char country_id_s [2];
   char ex_customer_s [5];
   char account_id_s [16];
   char filler_1_s;
} prop_trade_account_t;


typedef struct prop_deliv_account
{
   char country_id_s [2];
   char ex_customer_s [5];
   char account_id_s [16];
   char filler_1_s;
} prop_deliv_account_t;


typedef struct prop_pos_account
{
   char country_id_s [2];
   char ex_customer_s [5];
   char account_id_s [16];
   char filler_1_s;
} prop_pos_account_t;


typedef struct prop_margin_account
{
   char country_id_s [2];
   char ex_customer_s [5];
   char account_id_s [16];
   char filler_1_s;
} prop_margin_account_t;


typedef struct sink_account
{
   char country_id_s [2];
   char ex_customer_s [5];
   char account_id_s [16];
   char filler_1_s;
} sink_account_t;


typedef struct prop_origin_account
{
   char country_id_s [2];
   char ex_customer_s [5];
   char account_id_s [16];
   char filler_1_s;
} prop_origin_account_t;


typedef struct prop_call_account
{
   char country_id_s [2];
   char ex_customer_s [5];
   char account_id_s [16];
   char filler_1_s;
} prop_call_account_t;


typedef struct prop_settlement_account
{
   char country_id_s [2];
   char ex_customer_s [5];
   char account_id_s [16];
   char filler_1_s;
} prop_settlement_account_t;


typedef struct delivery_account
{
   char country_id_s [2];
   char ex_customer_s [5];
   char account_id_s [16];
   char filler_1_s;
} delivery_account_t;


typedef struct deliv_base
{
   uint8_t country_c;
   uint8_t market_c;
   uint8_t instrument_group_c;
   uint8_t modifier_c;
   uint16_t commodity_n;
   uint16_t expiration_date_n;
   int32_t strike_price_i;
} deliv_base_t;


typedef struct party
{
   char country_id_s [2];
   char ex_customer_s [5];
   char filler_1_s;
} party_t;


typedef struct participant
{
   char country_id_s [2];
   char ex_customer_s [5];
   char filler_1_s;
} participant_t;


/*   NAMED STRUCT = 50016  */

typedef struct trading_code
{
   char country_id_s [2];
   char ex_customer_s [5];
   char user_id_s [5];
} trading_code_t;


typedef struct tick_size
{
   int32_t step_size_i;
   int32_t lower_limit_i;
   int32_t upper_limit_i;
} tick_size_t;


typedef struct transaction_type_low
{
   transaction_type_t transaction_type;
} transaction_type_low_t;


typedef struct transaction_type_high
{
   transaction_type_t transaction_type;
} transaction_type_high_t;


typedef struct series_fields_used
{
   uint8_t country_c;
   uint8_t market_c;
   uint8_t instrument_group_c;
   uint8_t modifier_c;
   uint16_t commodity_n;
   uint16_t expiration_date_n;
   int32_t strike_price_i;
} series_fields_used_t;


typedef struct partition_low
{
   uint8_t country_c;
   uint8_t market_c;
   uint8_t instrument_group_c;
   uint8_t modifier_c;
   uint16_t commodity_n;
   uint16_t expiration_date_n;
   int32_t strike_price_i;
} partition_low_t;


typedef struct partition_high
{
   uint8_t country_c;
   uint8_t market_c;
   uint8_t instrument_group_c;
   uint8_t modifier_c;
   uint16_t commodity_n;
   uint16_t expiration_date_n;
   int32_t strike_price_i;
} partition_high_t;


typedef struct new_series
{
   uint8_t country_c;
   uint8_t market_c;
   uint8_t instrument_group_c;
   uint8_t modifier_c;
   uint16_t commodity_n;
   uint16_t expiration_date_n;
   int32_t strike_price_i;
} new_series_t;


typedef struct ex_user_code
{
   char country_id_s [2];
   char ex_customer_s [5];
   char user_id_s [5];
} ex_user_code_t;


typedef struct user_code
{
   char country_id_s [2];
   char ex_customer_s [5];
   char user_id_s [5];
} user_code_t;


typedef struct new_account
{
   char country_id_s [2];
   char ex_customer_s [5];
   char account_id_s [16];
   char filler_1_s;
} new_account_t;


typedef struct order_var
{
   int64_t mp_quantity_i;
   int32_t premium_i;
   uint32_t block_n;
   uint16_t time_validity_n;
   uint16_t exch_order_type_n;
   uint16_t trigger_order_time_validity_n;
   char ex_client_s [16];
   char customer_info_s [15];
   uint8_t open_close_req_c;
   uint8_t bid_or_ask_c;
   uint8_t ext_t_state_c;
   uint8_t order_type_c;
   uint8_t stop_condition_c;
   char filler_2_s [2];
} order_var_t;


/*   NAMED STRUCT = 50002  */

typedef struct give_up_member
{
   char country_id_s [2];
   char ex_customer_s [5];
   char filler_1_s;
} give_up_member_t;


typedef struct combo_series
{
   uint8_t country_c;
   uint8_t market_c;
   uint8_t instrument_group_c;
   uint8_t modifier_c;
   uint16_t commodity_n;
   uint16_t expiration_date_n;
   int32_t strike_price_i;
} combo_series_t;


typedef struct upper_level_series
{
   uint8_t country_c;
   uint8_t market_c;
   uint8_t instrument_group_c;
   uint8_t modifier_c;
   uint16_t commodity_n;
   uint16_t expiration_date_n;
   int32_t strike_price_i;
} upper_level_series_t;


typedef struct status_item
{
   char field_s [32];
   char stat_description_s [80];
} status_item_t;


typedef struct account_data
{
   account_t account;
   countersign_t countersign;
   prop_trade_account_t prop_trade_account;
   prop_deliv_account_t prop_deliv_account;
   prop_pos_account_t prop_pos_account;
   prop_margin_account_t prop_margin_account;
   sink_account_t sink_account;
   prop_origin_account_t prop_origin_account;
   prop_call_account_t prop_call_account;
   account_t prop_non_ccp_margin_account;
   prop_settlement_account_t prop_settlement_account;
   int32_t rank_class_i;
   char risk_currency_s [3];
   char modified_date_s [8];
   char modified_time_s [6];
   char created_date_s [8];
   char created_time_s [6];
   char investor_type_s [4];
   char nationality_s [4];
   char account_text_s [20];
   char ext_acc_id_s [34];
   char ext_acc_controller_s [15];
   char ext_acc_registrar_s [12];
   char org_number_s [16];
   char account_alias_s [32];
   char diary_number_s [15];
   char acc_type_s [12];
   char fee_type_s [12];
   char cust_bank_id_s [12];
   uint8_t acc_state_c;
   uint8_t read_access_c;
   uint8_t auto_net_c;
   uint8_t risk_cur_conv_c;
   uint8_t risk_margin_net_c;
   uint8_t acc_allow_nov_c;
   uint8_t cash_collateral_interest_c;
   uint8_t dd_in_base_c;
   uint8_t foreign_holder_c;
} account_data_t;


typedef struct cl_delivery_api
{
   account_t account;
   delivery_account_t delivery_account;
   series_t series;
   deliv_base_t deliv_base;
   int64_t deliv_base_quantity_q;
   int64_t delivery_quantity_q;
   int32_t delivery_number_i;
   int32_t key_number_i;
   int32_t delivery_origin_i;
   int32_t class_no_i;
   int32_t sequence_number_i;
   int32_t event_type_i;
   int32_t original_delivery_number_i;
   int32_t original_key_number_i;
   uint32_t delivery_unit_u;
   uint32_t delivery_properties_u;
   uint32_t propagation_u;
   char settlement_date_s [8];
   char date_s [8];
   account_t clearing_account;
   char original_date_s [8];
   char passthrough_s [32];
   uint8_t delivery_type_c;
   uint8_t originator_type_c;
   uint8_t delivery_state_c;
   uint8_t bought_or_sold_c;
   char ext_trade_fee_type_c;
   char giving_up_exchange_s [2];
   char settlement_instr_date_s [8];
   char filler_1_s;
} cl_delivery_api_t;


typedef struct cl_give_up_api
{
   series_t series;
   account_t account;
   party_t party;
   int32_t sequence_number_i;
   int32_t gup_reason_i;
   int32_t give_up_number_i;
   int64_t trade_quantity_i;
   int32_t deal_price_i;
   int32_t trade_number_i;
   int32_t commission_i;
   uint8_t bought_or_sold_c;
   uint8_t state_c;
   char created_date_s [8];
   char created_time_s [6];
   char give_up_text_s [30];
   char asof_date_s [8];
   char asof_time_s [6];
   char orig_clearing_date_s [8];
   uint8_t old_trade_c;
   char ext_trade_fee_type_c;
   uint8_t deal_source_c;
   uint8_t reserved_prop_c;
   char clearing_date_s [8];
   uint32_t ext_trade_number_u;
   uint32_t orig_ext_trade_number_u;
   uint8_t trade_venue_c;
   char filler_3_s [3];
} cl_give_up_api_t;


typedef struct old_series
{
   uint8_t country_c;
   uint8_t market_c;
   uint8_t instrument_group_c;
   uint8_t modifier_c;
   uint16_t commodity_n;
   uint16_t expiration_date_n;
   int32_t strike_price_i;
} old_series_t;


typedef struct time_spec
{
   uint32_t tv_sec;
   int32_t tv_nsec;
} time_spec_t;


typedef struct currency_ranking_connection
{
   account_t account;
   participant_t participant;
   char currency_ranking_id_s [32];
} currency_ranking_connection_t;


typedef struct ccy_rnk_cnx_attributes
{
   int32_t version_i;
   char created_date_s [8];
   char created_time_s [6];
   char modified_date_s [8];
   char modified_time_s [6];
   trading_code_t trading_code;
   uint8_t le_state_c;
   char filler_3_s [3];
} ccy_rnk_cnx_attributes_t;


typedef struct ref_delta_limits
{
   int32_t upper_limit_i;
   int32_t lower_limit_i;
   char price_limit_unit_c;
   char filler_3_s [3];
} ref_delta_limits_t;


typedef struct last_delta_limits
{
   int32_t upper_limit_i;
   int32_t lower_limit_i;
   char price_limit_unit_c;
   char filler_3_s [3];
} last_delta_limits_t;


typedef struct da24
{
   uint8_t country_c;
   char name_s [32];
   char exchange_short_s [4];
   char country_id_s [2];
   char tz_exchange_s [40];
   char master_clh_id_s [12];
   char country_s [2];
   char date_implementation_s [8];
   char filler_3_s [3];
} da24_t;


typedef struct cl_trade_change_api
{
   series_t series;
   int32_t trade_number_i;
   int32_t sequence_number_i;
   uint8_t trade_state_c;
   uint8_t le_state_c;
   uint8_t give_up_state_c;
   uint8_t instance_c;
   int64_t rem_quantity_i;
   char modified_date_s [8];
   char modified_time_s [6];
   char filler_2_s [2];
   uint32_t big_attention_u;
} cl_trade_change_api_t;


typedef struct server_partition
{
   char server_name_s [20];
   transaction_type_low_t transaction_type_low;
   transaction_type_high_t transaction_type_high;
   series_fields_used_t series_fields_used;
   partition_low_t partition_low;
   partition_high_t partition_high;
   int32_t event_type_i;
} server_partition_t;


typedef struct orig_deal_part
{
   series_t series;
   char asof_date_s [8];
   char asof_time_s [6];
   char filler_2_s [2];
   int32_t deal_price_i;
   int32_t deal_number_i;
   int64_t deal_quantity_i;
} orig_deal_part_t;


typedef struct rectify_deal_part
{
   new_series_t new_series;
   char modified_date_s [8];
   char modified_time_s [6];
   char asof_date_s [8];
   char asof_time_s [6];
   int64_t rectify_deal_number_q;
   trading_code_t trading_code;
   ex_user_code_t ex_user_code;
   int32_t state_i;
   int32_t new_deal_price_i;
} rectify_deal_part_t;


typedef struct ans_rect_t_item
{
   char created_date_s [8];
   char created_time_s [6];
   char asof_date_s [8];
   char asof_time_s [6];
   char clearing_date_s [8];
   char orig_clearing_date_s [8];
   trading_code_t trading_code;
   user_code_t user_code;
   series_t series;
   int32_t trade_number_i;
   int32_t rectify_trade_number_i;
   int32_t ext_seq_nbr_i;
   uint8_t state_c;
   uint8_t bought_or_sold_c;
   uint8_t reserved_prop_c;
   char filler_1_s;
   new_account_t new_account;
   account_t account;
   int64_t trade_quantity_i;
   int32_t deal_price_i;
} ans_rect_t_item_t;


typedef struct order_no_id
{
   series_t series;
   int64_t mp_quantity_i;
   int32_t premium_i;
   uint32_t block_n;
   uint16_t exch_order_type_n;
   uint8_t bid_or_ask_c;
   char filler_1_s;
} order_no_id_t;


typedef struct order
{
   series_t series;
   trading_code_t trading_code;
   order_var_t order_var;
   ex_user_code_t ex_user_code;
   give_up_member_t give_up_member;
   char exchange_info_s [32];
   uint32_t order_index_u;
   uint16_t transaction_number_n;
   uint8_t change_reason_c;
   char filler_1_s;
} order_t;


typedef struct pos_info_update_api
{
   series_t series;
   account_t account;
   int64_t deny_exercise_q;
   int64_t qty_closed_out_q;
   uint32_t quantity_cover_u;
   char modified_date_s [8];
   char modified_time_s [6];
   uint8_t reserved_prop_c;
   char filler_1_s;
} pos_info_update_api_t;


typedef struct da5
{
   combo_series_t combo_series;
   char cbs_id_s [32];
   uint8_t items_c;
   char filler_3_s [3];
   struct	
   {	
      series_t series;
      uint16_t ratio_n;
      char op_if_buy_c;
      char op_if_sell_c;
   } item [24];
} da5_t;


typedef struct trd_rpt_cust
{
   party_t party;
   char ex_client_s [16];
   char customer_info_s [15];
   char exchange_info_s [32];
   uint8_t open_close_req_c;
   uint16_t exch_order_type_n;
   give_up_member_t give_up_member;
   char filler_2_s [2];
} trd_rpt_cust_t;


typedef struct da53
{
   series_t series;
   char corp_action_code_s [2];
   uint8_t corp_action_type_c;
   uint8_t corp_action_status_c;
   uint8_t corp_action_level_c;
   char filler_3_s [3];
} da53_t;


/*   NAMED STRUCT = 18074  */

typedef struct deposit_withdraw_collateral_ssi
{
   account_t account;
   int64_t amount_q;
   int64_t gross_amount_q;
   int64_t ssi_id_q;
   char isin_code_s [12];
   char passthrough_s [32];
   char instr_ref_s [16];
   char cancel_ref_s [16];
   char csd_code_s [34];
   char reason_s [80];
   char currency_s [3];
   char filler_1_s;
   uint16_t dec_in_amount_n;
   uint8_t collateral_transaction_type_c;
   uint8_t collateral_transaction_state_c;
   char clh_account_id_s [32];
   char filler_2_s [2];
} deposit_withdraw_collateral_ssi_t;


typedef struct delta_limits
{
   int32_t upper_limit_i;
   int32_t lower_limit_i;
   uint16_t price_source_rule_n;
   char price_limit_unit_c;
   char filler_1_s;
} delta_limits_t;


typedef struct originator_trading_code
{
   char country_id_s [2];
   char ex_customer_s [5];
   char user_id_s [5];
} originator_trading_code_t;


typedef struct prop_delivery_account
{
   char country_id_s [2];
   char ex_customer_s [5];
   char account_id_s [16];
   char filler_1_s;
} prop_delivery_account_t;


typedef struct cash_opt_account
{
   char country_id_s [2];
   char ex_customer_s [5];
   char account_id_s [16];
   char filler_1_s;
} cash_opt_account_t;


typedef struct da9
{
   series_t series;
   upper_level_series_t upper_level_series;
   int32_t contract_size_i;
   int32_t price_quot_factor_i;
   uint16_t state_number_n;
   char ins_id_s [32];
   char isin_code_s [12];
   uint8_t stopped_by_issue_c;
   char isin_code_old_s [12];
   char date_notation_s [8];
   char date_last_trading_s [8];
   char time_last_trading_s [6];
   char date_delivery_start_s [8];
   char date_delivery_stop_s [8];
   uint8_t deliverable_c;
   uint8_t suspended_c;
   uint8_t series_status_c;
   uint8_t tm_template_c;
   uint8_t tm_series_c;
   char settlement_date_s [8];
   char start_date_s [8];
   char end_date_s [8];
   uint8_t accept_collateral_c;
   char date_first_trading_s [8];
   char time_first_trading_s [6];
   uint8_t traded_in_click_c;
   uint8_t traded_c;
   char effective_exp_date_s [8];
   char filler_1_s;
} da9_t;


typedef struct da2
{
   series_t series;
   upper_level_series_t upper_level_series;
   int32_t contract_size_i;
   int32_t price_quot_factor_i;
   uint32_t series_sequence_number_u;
   uint16_t state_number_n;
   uint16_t step_size_multiple_n;
   char ins_id_s [32];
   char isin_code_s [12];
   uint8_t suspended_c;
   char date_last_trading_s [8];
   char time_last_trading_s [6];
   char settlement_date_s [8];
   char start_date_s [8];
   char end_date_s [8];
   char date_delivery_start_s [8];
   char date_delivery_stop_s [8];
   uint8_t series_status_c;
   char long_ins_id_s [32];
   char date_first_trading_s [8];
   char time_first_trading_s [6];
   uint8_t traded_in_click_c;
   char abbr_name_s [8];
   char stock_code_s [6];
   uint8_t ext_info_source_c;
   char effective_exp_date_s [8];
   char filler_2_s [2];
} da2_t;


typedef struct trd_rpt_part
{
   party_t party;
   char ex_client_s [16];
   char customer_info_s [15];
   char exchange_info_s [32];
   uint8_t open_close_req_c;
} trd_rpt_part_t;


typedef struct aat_rg_connection_status_item
{
   account_t account;
   int32_t aat_connection_status_i;
} aat_rg_connection_status_item_t;


typedef struct broadcast_type
{
   char central_module_c;
   char server_type_c;
   uint16_t transaction_number_n;
} broadcast_type_t;


typedef struct da13
{
   char fee_type_s [12];
   char description_s [40];
} da13_t;


typedef struct account_status_item
{
   status_item_t status_item;
} account_status_item_t;


typedef struct da12
{
   char acc_type_s [12];
   char description_s [40];
   uint8_t open_close_c;
   uint8_t transitory_c;
   uint8_t market_maker_c;
   uint8_t own_inventory_c;
   uint8_t exclusive_opening_sell_c;
   uint8_t positions_allowed_c;
   uint8_t trades_allowed_c;
   char atr_id_s [12];
   char origin_c;
   uint8_t handled_non_ccp_c;
   uint8_t custodian_c;
   char filler_2_s [2];
} da12_t;


typedef struct add_tm_combo_item
{
   series_t series;
   uint16_t ratio_n;
   char op_if_buy_c;
   char op_if_sell_c;
} add_tm_combo_item_t;


typedef struct answer_account_ext_item
{
   account_data_t account_data;
} answer_account_ext_item_t;


typedef struct answer_account_fee_type_item
{
   char fee_type_s [12];
   char description_s [40];
} answer_account_fee_type_item_t;


typedef struct answer_account_type_item
{
   char acc_type_s [12];
   char description_s [40];
   uint8_t open_close_c;
   uint8_t transitory_c;
   uint8_t market_maker_c;
   uint8_t own_inventory_c;
   uint8_t exclusive_opening_sell_c;
   uint8_t positions_allowed_c;
   uint8_t trades_allowed_c;
   char atr_id_s [12];
   char origin_c;
   uint8_t handled_non_ccp_c;
   uint8_t custodian_c;
   char filler_2_s [2];
} answer_account_type_item_t;


typedef struct answer_account_type_rule_item
{
   char atr_id_s [12];
   uint8_t create_over_api_c;
   uint8_t activate_at_reg_c;
   uint16_t account_field_no_n;
   uint8_t attribute_rule_c;
   char filler_3_s [3];
} answer_account_type_rule_item_t;


typedef struct answer_acc_access_type_item
{
   account_t account;
   char created_date_s [8];
   char created_time_s [6];
   char modified_date_s [8];
   char modified_time_s [6];
   uint8_t le_state_c;
   char filler_3_s [3];
   trading_code_t trading_code;
} answer_acc_access_type_item_t;


typedef struct answer_api_delivery_item
{
   cl_delivery_api_t cl_delivery_api;
} answer_api_delivery_item_t;


typedef struct answer_api_give_up_item
{
   cl_give_up_api_t cl_give_up_api;
} answer_api_give_up_item_t;


typedef struct answer_authorized_report_item
{
   int32_t report_no_i;
   char country_id_s [2];
   char ex_customer_s [5];
   char report_name_s [64];
   char report_template_s [64];
   char report_template_desc_s [64];
   char report_file_prefix_s [9];
   uint8_t report_file_ext_c;
   char report_spec_s [5];
   char report_spec_desc_s [32];
   uint8_t report_owner_type_c;
   char csb_id_s [12];
   char css_id_s [12];
   char bank_id_s [12];
   char clh_id_s [12];
   char filler_1_s;
} answer_authorized_report_item_t;


typedef struct answer_average_price_trade_item
{
   int32_t trade_number_i;
   int64_t quantity_i;
} answer_average_price_trade_item_t;


typedef struct answer_bi26_signals_sent_item
{
   int32_t info_type_i;
   char date_s [8];
   char clearing_date_s [8];
   char clh_id_s [12];
   char sent_date_s [8];
   char sent_time_s [6];
   char filler_2_s [2];
} answer_bi26_signals_sent_item_t;


typedef struct answer_bi27_broadcasts_sent_item1
{
   uint16_t broadcast_number_n;
   uint8_t country_c;
   uint8_t market_c;
   char yyyymmdd_s [8];
   char hhmmss_s [6];
   uint16_t items_n;
   char filler_2_s [2];
   struct	
   {	
      char free_text_80_s [80];
   } item2 [10];
} answer_bi27_broadcasts_sent_item1_t;


typedef struct answer_bi73_signals_sent_item
{
   series_t series;
   int32_t info_type_i;
   char business_date_s [8];
   char clearing_date_s [8];
   char sent_date_s [8];
   char sent_time_s [6];
   uint16_t seq_num_srm_n;
} answer_bi73_signals_sent_item_t;


typedef struct answer_bi7_signals_sent_item
{
   series_t series;
   int32_t info_type_i;
   char business_date_s [8];
   char clearing_date_s [8];
   char sent_date_s [8];
   char sent_time_s [6];
   uint16_t seq_num_srm_n;
} answer_bi7_signals_sent_item_t;


typedef struct answer_broker_item
{
   char user_id_s [5];
   uint8_t program_trader_c;
   uint16_t cst_id_n;
   uint16_t usr_id_n;
   uint16_t items_n;
   struct	
   {	
      series_t series;
   } item [100];
} answer_broker_item_t;


typedef struct answer_central_group_item
{
   char central_group_s [12];
   uint16_t leg_number_n;
   uint8_t sort_type_c;
   char filler_1_s;
   char long_ins_id_s [32];
} answer_central_group_item_t;


typedef struct answer_clearing_date_item
{
   series_t series;
   char clearing_date_s [8];
   char next_clearing_date_s [8];
   char prev_clearing_date_s [8];
   char tra_cl_next_day_c;
   char filler_3_s [3];
} answer_clearing_date_item_t;


typedef struct answer_closeout_log_item
{
   trading_code_t trading_code;
   series_t series;
   account_t account;
   int64_t closeout_qty_i;
   char date_s [8];
   char created_date_s [8];
   char created_time_s [6];
   uint8_t open_close_c;
   uint8_t state_c;
} answer_closeout_log_item_t;


typedef struct answer_combo_item
{
   combo_series_t combo_series;
   char cbs_id_s [32];
   uint8_t items_c;
   char filler_3_s [3];
   struct	
   {	
      series_t series;
      uint16_t ratio_n;
      char op_if_buy_c;
      char op_if_sell_c;
   } item [24];
} answer_combo_item_t;


typedef struct answer_commission_item
{
   series_t series;
   party_t party;
   char account_id_s [16];
   char customer_info_s [15];
   char created_date_s [8];
   char created_time_s [6];
   char user_code_s [12];
   char filler_3_s [3];
   int32_t commission_i;
} answer_commission_item_t;


typedef struct answer_conf_give_up_req_items_item
{
   account_t account;
   int64_t trade_quantity_i;
   uint8_t open_close_req_c;
   char customer_info_s [15];
} answer_conf_give_up_req_items_item_t;


typedef struct answer_converted_series_item
{
   uint16_t adjust_ident_n;
   char filler_2_s [2];
   int32_t contract_size_i;
   int32_t price_quot_factor_i;
   old_series_t old_series;
   new_series_t new_series;
} answer_converted_series_item_t;


typedef struct answer_cool_off_period_ended_item
{
   series_t series;
   time_spec_t timestamp;
   int32_t lower_limit_i;
   int32_t upper_limit_i;
   uint8_t cool_off_ended_type_c;
   char price_limit_unit_c;
   char filler_2_s [2];
} answer_cool_off_period_ended_item_t;


typedef struct answer_corp_action_da53_item
{
   series_t series;
   char corp_action_code_s [2];
   uint8_t corp_action_type_c;
   uint8_t corp_action_status_c;
   uint8_t corp_action_level_c;
   char filler_3_s [3];
} answer_corp_action_da53_item_t;


typedef struct answer_currency_item
{
   uint16_t sec_rel_primary_n;
   uint16_t third_rel_primary_n;
   char base_cur_s [3];
   char pri_unit_s [15];
   char sec_unit_s [15];
   char third_unit_s [15];
   char pri_not_s [5];
   char sec_not_s [5];
   char third_not_s [5];
   uint8_t acc_as_pay_c;
} answer_currency_item_t;


typedef struct answer_currency_ranking_connections_item
{
   currency_ranking_connection_t currency_ranking_connection;
   ccy_rnk_cnx_attributes_t ccy_rnk_cnx_attributes;
} answer_currency_ranking_connections_item_t;


typedef struct answer_deal_source_item
{
   int64_t ds_attribute_q;
   int16_t deal_source_n;
   char desc_long_s [128];
   char desc_abbreviated_s [32];
   char filler_2_s [2];
} answer_deal_source_item_t;


typedef struct answer_delivery_item
{
   char date_s [8];
   int32_t event_type_i;
   series_t series;
   account_t account;
   int32_t class_no_i;
   int64_t deliv_base_quantity_q;
   char settlement_date_s [8];
   int64_t delivery_quantity_q;
   deliv_base_t deliv_base;
} answer_delivery_item_t;


typedef struct answer_delta_limit_item
{
   series_t series;
   ref_delta_limits_t ref_delta_limits;
   last_delta_limits_t last_delta_limits;
   int32_t price_u_calc_limit_i;
   int32_t price_l_calc_limit_i;
} answer_delta_limit_item_t;


typedef struct answer_error_msg_item
{
   trading_code_t trading_code;
   series_t series;
   account_t account;
   char created_date_s [8];
   char created_time_s [6];
   char error_operation_s [10];
   uint32_t error_id_u;
   char error_problem_s [40];
} answer_error_msg_item_t;


typedef struct answer_etpr_delta_limit_item
{
   series_t series;
   ref_delta_limits_t ref_delta_limits;
   int32_t price_u_calc_limit_i;
   int32_t price_l_calc_limit_i;
   int32_t reference_premium_i;
} answer_etpr_delta_limit_item_t;


typedef struct answer_exception_days_item
{
   series_t series;
   char date_exception_s [8];
} answer_exception_days_item_t;


typedef struct answer_exchange_da24_item
{
   da24_t da24;
} answer_exchange_da24_item_t;


typedef struct answer_exchange_rate_item
{
   int32_t rate_nominal_i;
   int32_t price_quot_factor_i;
   int32_t rate_low_i;
   int32_t rate_high_i;
   uint16_t dec_in_rate_n;
   uint16_t dec_in_contr_size_n;
   char price_currency_s [3];
   char other_currency_s [3];
   char filler_2_s [2];
} answer_exchange_rate_item_t;


typedef struct answer_exercise_req_item
{
   series_t series;
   account_t account;
   char reserved_1_c;
   char reserved_2_s [2];
   char filler_1_s;
   trading_code_t trading_code;
   ex_user_code_t ex_user_code;
   char modified_date_s [8];
   char modified_time_s [6];
   char asof_date_s [8];
   char asof_time_s [6];
   int64_t quantity_i;
   int32_t trade_number_i;
   int32_t exercise_number_i;
   uint8_t state_c;
   char filler_3_s [3];
} answer_exercise_req_item_t;


typedef struct answer_fixing_dates_item
{
   char reg_cl_date_s [8];
   char date_s [8];
   int32_t fixing_value_i;
   uint16_t dec_in_fixing_n;
   char filler_2_s [2];
} answer_fixing_dates_item_t;


typedef struct answer_fixing_val_item
{
   series_t series;
   int32_t fixing_value_i;
   uint16_t dec_in_fixing_n;
   char filler_2_s [2];
} answer_fixing_val_item_t;


typedef struct answer_give_up_request_item
{
   series_t series;
   account_t account;
   party_t party;
   int32_t give_up_number_i;
   int64_t trade_quantity_i;
   int32_t deal_price_i;
   int32_t trade_number_i;
   int32_t commission_i;
   uint8_t bought_or_sold_c;
   uint8_t state_c;
   char created_date_s [8];
   char created_time_s [6];
   char give_up_text_s [30];
   char asof_date_s [8];
   char asof_time_s [6];
   char orig_clearing_date_s [8];
   uint8_t old_trade_c;
   char ext_trade_fee_type_c;
   uint8_t deal_source_c;
   uint8_t reserved_prop_c;
   char clearing_date_s [8];
   uint32_t ext_trade_number_u;
   uint32_t orig_ext_trade_number_u;
} answer_give_up_request_item_t;


typedef struct answer_greeks_item
{
   series_t series;
   int32_t delta_i;
   int32_t gamma_i;
   int32_t vega_i;
   int32_t theta_i;
   int32_t rho_i;
} answer_greeks_item_t;


typedef struct answer_haircut_item
{
   series_t series;
   char description_s [40];
   uint32_t haircut_rate_u;
   uint32_t time_to_maturity_u;
} answer_haircut_item_t;


typedef struct answer_instrument_item
{
   series_t series;
   uint32_t min_show_vol_u;
   uint16_t hidden_vol_meth_n;
   uint16_t pub_inf_id_n;
   char int_id_s [8];
   char name_s [32];
   uint8_t maintain_positions_c;
   uint8_t traded_c;
   uint8_t post_trade_proc_c;
   uint8_t pos_handling_c;
   uint8_t directed_trade_information_c;
   uint8_t public_deal_information_c;
   uint8_t pricing_method_c;
   uint8_t settlement_type_c;
} answer_instrument_item_t;


typedef struct answer_instrument_class_item
{
   series_t series;
   upper_level_series_t upper_level_series;
   int32_t price_quot_factor_i;
   int32_t contract_size_i;
   int32_t exerc_limit_i;
   int32_t redemption_value_i;
   int32_t min_qty_increment_i;
   uint16_t derivate_level_n;
   uint16_t dec_in_strike_price_n;
   uint16_t dec_in_contr_size_n;
   uint16_t rnt_id_n;
   uint16_t dec_in_premium_n;
   uint16_t items_n;
   struct	
   {	
      tick_size_t tick_size;
   } item [12];
   uint16_t dec_in_deliv_n;
   uint16_t items_block_n;
   struct	
   {	
      int64_t maximum_size_u;
      uint32_t minimum_size_n;
      uint32_t block_n;
      uint8_t lot_type_c;
      char filler_3_s [3];
   } block_size [4];
   uint16_t cleared_dec_in_qty_n;
   uint16_t virt_commodity_n;
   uint16_t dec_in_fixing_n;
   char base_cur_s [3];
   uint8_t traded_c;
   uint8_t exerc_limit_unit_c;
   char inc_id_s [14];
   char trc_id_s [10];
   char name_s [32];
   char is_fractions_c;
   uint8_t price_unit_premium_c;
   uint8_t price_unit_strike_c;
   char settl_cur_id_s [32];
   char credit_class_s [3];
   char csd_id_s [12];
   uint8_t trd_cur_unit_c;
   uint8_t collateral_type_c;
   uint8_t fixing_req_c;
   char mbs_id_s [2];
   char valuation_group_id_s [12];
   uint8_t gross_settlement_c;
   char filler_1_s;
} answer_instrument_class_item_t;


typedef struct answer_instrument_group_item
{
   uint8_t instrument_group_c;
   char name_s [32];
   char ing_id_s [3];
   uint8_t group_type_c;
   uint8_t tailor_made_c;
   uint8_t option_type_c;
   uint8_t option_style_c;
   uint8_t warrant_c;
   uint8_t repo_type_c;
   uint8_t buy_sell_back_c;
   uint8_t future_styled_c;
   uint8_t is_exclusive_opening_sell_c;
   uint8_t knock_variant_c;
   uint8_t binary_variant_c;
   uint8_t option_variant_c;
   uint8_t physical_delivery_c;
   uint8_t forward_style_c;
   uint8_t swap_style_c;
   uint8_t maturity_c;
   char group_short_name_s [15];
   uint8_t overnight_index_swap_c;
} answer_instrument_group_item_t;


typedef struct answer_instrument_status_item
{
   series_t series;
   uint16_t state_number_n;
   uint16_t state_level_e;
} answer_instrument_status_item_t;


typedef struct answer_limit_item
{
   series_t series;
   int32_t upper_limit_i;
   int32_t lower_limit_i;
   int32_t reference_premium_i;
   uint16_t price_source_rule_n;
   char filler_2_s [2];
} answer_limit_item_t;


typedef struct answer_manual_payments_item
{
   series_t series;
   account_t account;
   char settlement_date_s [8];
   int64_t amount_u;
   char invc_text_s [60];
   char currency_s [3];
   uint8_t pay_or_receive_c;
   char settlement_instr_date_s [8];
} answer_manual_payments_item_t;


typedef struct answer_margin_acc_item
{
   account_t account;
   char market_currency_s [3];
   char filler_1_s;
   int64_t market_margin_q;
   int64_t risk_margin_q;
   char cust_bank_id_s [12];
   char risk_currency_s [3];
   uint8_t acc_risk_type_c;
   int64_t offset_reduction_adj_q;
} answer_margin_acc_item_t;


typedef struct answer_margin_data_used_item
{
   series_t series;
   char currency_s [3];
   uint8_t vol_src_c;
   int64_t margin_one_writ_opt_q;
   uint32_t bid_price_i;
   uint32_t ask_price_i;
   int32_t marg_price_i;
   int32_t fixing_value_i;
   int32_t val_ivl_mid_i;
   int32_t val_ivl_low_i;
   int32_t val_ivl_high_i;
   int32_t vol_ivl_held_mid_i;
   int32_t vol_ivl_writ_mid_i;
   int32_t vol_ivl_held_low_i;
   int32_t vol_ivl_writ_low_i;
   int32_t vol_ivl_held_high_i;
   int32_t vol_ivl_writ_high_i;
   int32_t remaining_contract_size_i;
   uint16_t dec_in_price_n;
   uint8_t opt_price_model_c;
   uint8_t opt_ulg_price_src_c;
   int32_t ulg_vola_i;
   int32_t flat_rate_increase_i;
   int32_t flat_rate_decrease_i;
   int32_t flat_rate_gain_discount_i;
   char filler_4_s [4];
} answer_margin_data_used_item_t;


typedef struct answer_margin_detail_item
{
   account_t account;
   series_t series;
   int64_t margin_req_u;
   int64_t market_value_q;
   int64_t nbr_held_q;
   int64_t nbr_written_q;
   int64_t held_marg_q;
   int64_t writ_marg_q;
   int64_t cash_margin_q;
   int64_t naked_margin_q;
   int64_t pay_margin_q;
   int64_t orig_market_value_q;
   int64_t unconv_market_value_q;
   uint32_t quantity_cover_u;
   char currency_s [3];
   uint8_t gross_or_net_c;
   char cash_currency_s [3];
   char margin_class_s [3];
   uint8_t marg_meth_inst_c;
   uint8_t marg_item_type_c;
} answer_margin_detail_item_t;


typedef struct answer_margin_ext_item
{
   series_t series;
   int64_t margin_req_u;
   int64_t market_value_q;
   account_t account;
   char currency_s [3];
   char filler_1_s;
} answer_margin_ext_item_t;


typedef struct answer_margin_mem_item
{
   char country_id_s [2];
   char ex_customer_s [5];
   char risk_currency_s [3];
   char cust_bank_id_s [12];
   char filler_2_s [2];
   int64_t risk_margin_q;
} answer_margin_mem_item_t;


typedef struct answer_margin_pa_acc_item
{
   account_t account;
   char market_currency_s [3];
   char filler_1_s;
   int64_t market_margin_q;
   int64_t market_value_q;
   int64_t cash_margin_q;
   uint8_t prod_area_c;
   uint8_t acc_risk_type_c;
   char prod_area_text_s [10];
   char cust_bank_id_s [12];
   int64_t offset_reduction_adj_q;
} answer_margin_pa_acc_item_t;


typedef struct answer_margin_prop_item
{
   account_t origin_margin_account;
   account_t margin_calc_account;
   int64_t premium_margin_q;
   int64_t risk_open_margin_q;
   int64_t pl_del_margin_q;
   int64_t risk_del_margin_q;
   int64_t pay_margin_q;
   int64_t var_margin_q;
   int64_t opt_premium_margin_q;
   int64_t long_opt_min_margin_q;
   int64_t additional_margin_q;
   int64_t flat_rate_margin_q;
   char currency_s [3];
   char source_s [10];
   uint8_t margin_has_propagated_c;
   char filler_2_s [2];
   int64_t pai_q;
} answer_margin_prop_item_t;


/*   NAMED STRUCT = 20025  */

typedef struct collection_id
{
   char valuation_date_s [8];
   int32_t sequence_number_n;
} collection_id_t;


typedef struct answer_margin_series_param_item
{
   series_t series;
   int64_t down_int_q;
   int64_t up_int_q;
   int32_t risk_free_rate_i;
   int32_t held_vol_down_i;
   int32_t held_vol_up_i;
   int32_t writ_vol_down_i;
   int32_t writ_vol_up_i;
   int32_t fixed_vol_i;
   int32_t held_for_adj_i;
   int32_t writ_for_adj_i;
   char pur_id_s [15];
   char win_id_s [15];
   char filler_2_s [2];
   int32_t bid_marg_vol_i;
   int32_t ask_marg_vol_i;
   int32_t dividend_yield_i;
   int32_t ind_bid_marg_vol_i;
   int32_t ind_ask_marg_vol_i;
} answer_margin_series_param_item_t;


typedef struct answer_margin_series_param_ext_item
{
   series_t series;
   int64_t down_int_q;
   int64_t up_int_q;
   int32_t risk_free_rate_i;
   int32_t held_vol_down_i;
   int32_t held_vol_up_i;
   int32_t writ_vol_down_i;
   int32_t writ_vol_up_i;
   int32_t fixed_vol_i;
   int32_t dividend_yield_i;
   char marg_param_id_s [15];
   char price_param_id_s [15];
   char win_id_s [15];
   char tdp_id_s [16];
   char filler_3_s [3];
} answer_margin_series_param_ext_item_t;


typedef struct answer_margin_ulg_price_item
{
   uint16_t commodity_n;
   char filler_2_s [2];
   uint32_t bid_price_i;
   uint32_t ask_price_i;
   int32_t marg_price_i;
   int32_t last_paid_i;
   uint8_t bid_theo_c;
   uint8_t ask_theo_c;
   uint8_t last_theo_c;
   uint8_t marg_theo_c;
} answer_margin_ulg_price_item_t;


typedef struct answer_marg_sim_add_trade_item
{
   series_t series;
   int64_t sim_qty_q;
   int32_t trade_price_sim_i;
   char closing_date_s [8];
   char date_settlement_s [8];
   uint8_t item_type_c;
   char filler_3_s [3];
   int32_t reserved_i;
   char reserved_8_s [8];
} answer_marg_sim_add_trade_item_t;


typedef struct answer_market_item
{
   uint16_t normal_trading_days_n;
   uint16_t normal_settl_days_n;
   uint16_t normal_clearing_days_n;
   uint8_t country_c;
   uint8_t market_c;
   char name_s [32];
   char mar_id_s [5];
   uint8_t market_type_c;
   uint8_t index_market_c;
   char bic_code_s [15];
   char mic_code_s [8];
   uint8_t tm_clearing_market_c;
   char filler_1_s;
} answer_market_item_t;


typedef struct answer_member_obligation_da57_item
{
   series_t series;
   uint16_t cst_id_n;
   char country_id_s [2];
   char ex_customer_s [5];
   uint8_t right_type_c;
   char filler_2_s [2];
} answer_member_obligation_da57_item_t;


typedef struct answer_missing_delivery_item
{
   cl_delivery_api_t cl_delivery_api;
} answer_missing_delivery_item_t;


typedef struct answer_missing_give_up_item
{
   cl_give_up_api_t cl_give_up_api;
} answer_missing_give_up_item_t;


typedef struct answer_missing_trade_change_item
{
   cl_trade_change_api_t cl_trade_change_api;
} answer_missing_trade_change_item_t;


typedef struct answer_mm_protection_item
{
   int64_t quantity_protection_q;
   int64_t delta_protection_q;
   int32_t exposure_time_interval_i;
   int32_t frozen_time_i;
   uint16_t commodity_n;
   char country_id_s [2];
   char ex_customer_s [5];
   uint8_t include_futures_c;
   char filler_2_s [2];
} answer_mm_protection_item_t;


typedef struct answer_non_trading_days_item
{
   uint8_t country_c;
   uint8_t market_c;
   char date_non_trading_s [8];
   uint8_t closed_for_trading_c;
   uint8_t closed_for_settlement_c;
   uint8_t closed_for_clearing_c;
   char filler_3_s [3];
} answer_non_trading_days_item_t;


typedef struct answer_non_trad_settl_days_item
{
   series_t series;
   char date_non_trading_s [8];
} answer_non_trad_settl_days_item_t;


typedef struct answer_open_interest_item
{
   series_t series;
   uint64_t final_open_interest_q;
} answer_open_interest_item_t;


typedef struct answer_open_interest_ext_item
{
   series_t series;
   uint64_t gross_open_interest_q;
   uint64_t net_open_interest_q;
   uint64_t member_net_open_interest_q;
} answer_open_interest_ext_item_t;


typedef struct answer_partition_item
{
   server_partition_t server_partition;
} answer_partition_item_t;


typedef struct answer_paynote_info_item
{
   series_t series;
   account_t account;
   char clearing_date_s [8];
   int32_t pay_note_number_i;
   uint8_t event_type_c;
   uint8_t settle_class_c;
   char filler_2_s [2];
   int64_t amount_u;
   char currency_s [3];
   uint8_t pay_or_receive_c;
   char settlement_instr_date_s [8];
   char settlement_date_s [8];
} answer_paynote_info_item_t;


typedef struct answer_position_item
{
   series_t series;
   char modified_date_s [8];
   char modified_time_s [6];
   uint8_t reserved_prop_c;
   char filler_1_s;
   int64_t nbr_held_q;
   int64_t nbr_written_q;
   int64_t deny_exercise_q;
   account_t account;
   uint32_t quantity_cover_u;
   int64_t qty_closed_out_q;
} answer_position_item_t;


typedef struct answer_prel_settlement_item
{
   series_t series;
   int32_t settl_price_i;
   char settlement_date_s [8];
   uint8_t settlement_price_type_c;
   char date_and_time_s [14];
   char filler_1_s;
} answer_prel_settlement_item_t;


typedef struct answer_price_limit_trigger_item
{
   series_t series;
   time_spec_t timestamp;
   int32_t lower_limit_i;
   int32_t upper_limit_i;
   int32_t next_lower_limit_i;
   int32_t next_upper_limit_i;
   int32_t cool_off_time_i;
   uint8_t tier_c;
   char price_limit_unit_c;
   char filler_2_s [2];
} answer_price_limit_trigger_item_t;


typedef struct answer_propagate_item
{
   account_t account;
   uint8_t prop_type_c;
   char filler_3_s [3];
} answer_propagate_item_t;


typedef struct answer_realtime_ulg_price_item
{
   uint32_t bid_price_i;
   uint32_t ask_price_i;
   int32_t last_paid_i;
   uint16_t commodity_n;
   uint8_t bid_theo_c;
   uint8_t ask_theo_c;
   uint8_t last_theo_c;
   char filler_3_s [3];
} answer_realtime_ulg_price_item_t;


typedef struct answer_rectify_d_item
{
   orig_deal_part_t orig_deal_part;
   rectify_deal_part_t rectify_deal_part;
} answer_rectify_d_item_t;


typedef struct answer_rectify_d_cont_item
{
   series_t series;
   int32_t trade_number_i;
   uint8_t bid_or_ask_c;
   char filler_3_s [3];
   int64_t trade_quantity_i;
} answer_rectify_d_cont_item_t;


typedef struct answer_rectify_ext_cont_item
{
   account_t account;
   int64_t trade_quantity_i;
   uint8_t open_close_req_c;
   char customer_info_s [15];
} answer_rectify_ext_cont_item_t;


typedef struct answer_rectify_t_item
{
   ans_rect_t_item_t ans_rect_t_item;
} answer_rectify_t_item_t;


typedef struct answer_report_nrs_item
{
   int32_t report_no_i;
   char country_id_s [2];
   char ex_customer_s [5];
   char report_spec_s [5];
   char clh_id_s [12];
   char business_date_s [8];
   char report_version_s [3];
   uint8_t ascii_bin_c;
   char file_name_s [80];
   char file_type_s [8];
   char created_date_s [8];
   char created_time_s [6];
   char filler_2_s [2];
} answer_report_nrs_item_t;


typedef struct answer_report_ver_item
{
   series_t series;
   int32_t info_type_i;
   char date_s [8];
   char country_id_s [2];
   char report_owner_s [12];
   char report_version_s [3];
   char name_s [32];
   char file_type_s [8];
   char description_s [40];
   uint8_t ascii_bin_c;
   char created_date_s [8];
   char created_time_s [6];
} answer_report_ver_item_t;


typedef struct answer_series_item
{
   series_t series;
   upper_level_series_t upper_level_series;
   int32_t contract_size_i;
   int32_t price_quot_factor_i;
   uint32_t series_sequence_number_u;
   uint16_t state_number_n;
   uint16_t step_size_multiple_n;
   char ins_id_s [32];
   char isin_code_s [12];
   uint8_t suspended_c;
   char date_last_trading_s [8];
   char time_last_trading_s [6];
   char settlement_date_s [8];
   char start_date_s [8];
   char end_date_s [8];
   char date_delivery_start_s [8];
   char date_delivery_stop_s [8];
   uint8_t series_status_c;
   char long_ins_id_s [32];
   char date_first_trading_s [8];
   char time_first_trading_s [6];
   uint8_t traded_in_click_c;
   char abbr_name_s [8];
   char stock_code_s [6];
   uint8_t ext_info_source_c;
   char effective_exp_date_s [8];
   char filler_2_s [2];
} answer_series_item_t;


typedef struct answer_series_bo_item
{
   series_t series;
   upper_level_series_t upper_level_series;
   int32_t contract_size_i;
   int32_t price_quot_factor_i;
   uint16_t state_number_n;
   char ins_id_s [32];
   char isin_code_s [12];
   uint8_t stopped_by_issue_c;
   char isin_code_old_s [12];
   char date_notation_s [8];
   char date_last_trading_s [8];
   char time_last_trading_s [6];
   char date_delivery_start_s [8];
   char date_delivery_stop_s [8];
   uint8_t deliverable_c;
   uint8_t suspended_c;
   uint8_t series_status_c;
   uint8_t tm_template_c;
   uint8_t tm_series_c;
   char settlement_date_s [8];
   char start_date_s [8];
   char end_date_s [8];
   uint8_t accept_collateral_c;
   char date_first_trading_s [8];
   char time_first_trading_s [6];
   uint8_t traded_in_click_c;
   uint8_t traded_c;
   char effective_exp_date_s [8];
   char filler_1_s;
} answer_series_bo_item_t;


typedef struct answer_state_type_item
{
   uint16_t state_type_number_n;
   char state_type_name_s [20];
   char name_s [32];
   uint8_t country_c;
   uint8_t market_c;
} answer_state_type_item_t;


typedef struct series_next
{
   uint8_t country_c;
   uint8_t market_c;
   uint8_t instrument_group_c;
   uint8_t modifier_c;
   uint16_t commodity_n;
   uint16_t expiration_date_n;
   int32_t strike_price_i;
} series_next_t;


typedef struct answer_tot_equil_prices_item
{
   series_t series;
   int64_t equilibrium_quantity_i;
   int32_t equilibrium_price_i;
   int32_t best_bid_premium_i;
   int32_t best_ask_premium_i;
   int64_t best_bid_quantity_i;
   int64_t best_ask_quantity_i;
   uint8_t matching_price_type_c;
   char filler_3_s [3];
} answer_tot_equil_prices_item_t;


typedef struct answer_tot_ob_item
{
   quad_word order_number_u;
   uint32_t sequence_number_u;
   uint32_t ob_position_u;
   uint8_t combo_mark_c;
   char filler_3_s [3];
   order_no_id_t order_no_id;
   party_t party;
} answer_tot_ob_item_t;


typedef struct answer_tot_order_item
{
   quad_word order_number_u;
   uint32_t sequence_number_u;
   uint32_t ob_position_u;
   uint8_t combo_mark_c;
   uint8_t order_category_c;
   uint16_t stp_key_i;
   party_t party;
   order_t order;
   int64_t total_volume_i;
   int64_t display_quantity_i;
   int64_t orig_shown_quantity_i;
   int64_t orig_total_volume_i;
   time_spec_t timestamp_in;
   time_spec_t timestamp_created;
   char filler_4_s [4];
} answer_tot_order_item_t;


typedef struct answer_trade_report_types_item
{
   int64_t initial_trr_min_value_u;
   char trc_id_s [10];
   char trr_id_s [4];
   char condition_s [32];
   uint8_t authorized_c;
   uint8_t ext_t_state_c;
   uint8_t allow_interbank_c;
   uint8_t allow_within_participant_c;
   uint8_t cbo_trade_report_c;
   uint8_t allow_non_std_settlement_c;
   uint8_t time_of_agree_req_c;
   uint8_t time_of_agree_gran_c;
   uint8_t allow_delayed_c;
   char filler_1_s;
} answer_trade_report_types_item_t;


typedef struct answer_trade_statistics_item
{
   series_t series;
   int32_t bid_premium_i;
   int32_t ask_premium_i;
   int32_t opening_price_i;
   int32_t settle_price_i;
   int32_t last_price_i;
   int32_t high_price_i;
   int32_t low_price_i;
   int64_t volume_today_i;
   int64_t volume_yesterday_i;
   int64_t turnaround_yesterday_u;
   int64_t turnaround_today_u;
   int64_t open_balance_u;
   int64_t revised_open_balance_u;
   int32_t volatility_i;
   int32_t underlying_price_i;
   int32_t corr_opening_price_i;
   int32_t corr_high_price_i;
   int32_t corr_low_price_i;
   int32_t corr_last_price_i;
   uint8_t bid_theo_c;
   uint8_t ask_theo_c;
   char filler_2_s [2];
} answer_trade_statistics_item_t;


typedef struct answer_trading_state_item
{
   char state_name_s [20];
   uint16_t state_number_n;
   uint16_t iss_def_warning_interval_n;
   uint16_t iss_def_num_of_warnings_n;
   uint16_t state_type_number_n;
   uint8_t continues_matching_c;
   uint8_t trading_end_c;
   uint8_t price_quotation_required_c;
   uint8_t market_orders_allowed_c;
   uint8_t fill_or_kill_allowed_c;
   uint8_t fill_and_kill_allowed_c;
   uint8_t edited_ob_changes_avail_c;
   uint8_t ob_changes_avail_c;
   uint8_t end_of_clearing_day_c;
   uint8_t state_priority_c;
   uint8_t fill_and_store_c;
   uint8_t all_or_none_c;
   uint8_t imb_orders_allwd_c;
   uint8_t mtl_orders_rlot_allwd_c;
   uint8_t allow_hidd_aggr_c;
   uint8_t best_limit_c;
   uint8_t market_bid_c;
   uint8_t price_stabilization_c;
   uint8_t short_sell_c;
   uint8_t allow_cp_mar_c;
   uint8_t allow_cp_lim_c;
   uint8_t allow_undisclosed_qty_c;
   uint8_t sso_orders_allowed_c;
   uint8_t stop_orders_allowed_c;
   uint8_t good_till_session_c;
   uint8_t priority_ranking_c;
   uint8_t fix_state_number_c;
   char filler_1_s;
} answer_trading_state_item_t;


typedef struct answer_trd_report_item
{
   trading_code_t trading_code;
   transaction_type_t transaction_type;
   quad_word order_number_u;
   series_t series;
   order_var_t order_var;
   party_t party;
   uint32_t sequence_number_u;
   char exchange_info_s [32];
   give_up_member_t give_up_member;
   char settlement_date_s [8];
   char time_of_agreement_date_s [8];
   char time_of_agreement_time_s [6];
   uint8_t deferred_publication_c;
   char filler_1_s;
} answer_trd_report_item_t;


typedef struct answer_trd_report_party_item
{
   trading_code_t trading_code;
   transaction_type_t transaction_type;
   quad_word order_number_u;
   series_t series;
   order_var_t order_var;
   party_t party;
   char exchange_info_s [32];
   give_up_member_t give_up_member;
   char settlement_date_s [8];
   char time_of_agreement_date_s [8];
   char time_of_agreement_time_s [6];
   uint8_t deferred_publication_c;
   char filler_1_s;
} answer_trd_report_party_item_t;


typedef struct answer_underlying_item
{
   int32_t subscription_price_i;
   int32_t interest_rate_i;
   uint16_t commodity_n;
   char com_id_s [6];
   char isin_code_s [12];
   uint16_t dec_in_price_n;
   char date_release_s [8];
   char date_termination_s [8];
   char date_dated_s [8];
   char name_s [32];
   char base_cur_s [3];
   uint8_t deliverable_c;
   uint16_t coupon_frequency_n;
   int64_t nominal_value_q;
   uint16_t day_count_n;
   uint16_t days_in_interest_year_n;
   uint32_t coupon_interest_i;
   uint16_t coupon_settlement_days_n;
   uint8_t underlying_type_c;
   uint8_t price_unit_c;
   uint16_t dec_in_nominal_n;
   uint16_t state_number_n;
   uint16_t linked_commodity_n;
   uint8_t fixed_income_type_c;
   uint8_t underlying_status_c;
   char underlying_issuer_s [6];
   char time_delivery_start_s [6];
   char time_delivery_stop_s [6];
   char sector_code_s [4];
   uint16_t items_n;
   struct	
   {	
      char date_coupdiv_s [8];
      uint32_t dividend_i;
   } coupon [80];
   uint8_t virtual_c;
   char member_circ_numb_s [4];
   char inv_scheme_c;
   char date_closing_s [8];
   char date_last_s [8];
   char country_id_s [2];
   uint8_t cur_unit_c;
   char filler_3_s [3];
} answer_underlying_item_t;


typedef struct answer_underlying_adjustment_item
{
   int64_t no_of_shares_issued_q;
   int64_t free_float_q;
   uint16_t adjust_ident_n;
   uint16_t commodity_n;
   char date_adjust_s [8];
   char date_conversion_s [8];
   uint8_t deal_price_modifier_c;
   uint8_t contract_size_modifier_c;
   uint8_t strike_price_modifier_c;
   uint8_t contracts_modifier_c;
   uint8_t und_price_modifier_c;
   uint8_t so_strike_price_modifier_c;
   uint8_t so_contract_size_modifier_c;
   uint8_t so_deal_price_modifier_c;
   int32_t deal_price_mod_factor_i;
   int32_t contr_size_mod_factor_i;
   int32_t strike_price_mod_factor_i;
   int32_t contracts_mod_factor_i;
   int32_t und_price_mod_factor_i;
   int32_t so_strike_price_mod_factor_i;
   int32_t so_contr_size_mod_factor_i;
   int32_t so_deal_price_mod_factor_i;
   int32_t pqf_mod_factor_i;
   int32_t so_pqf_mod_factor_i;
   uint16_t new_commodity_n;
   uint16_t so_commodity_n;
   uint8_t pqf_modifier_c;
   uint8_t so_pqf_modifier_c;
   uint8_t country_c;
   uint8_t market_c;
   uint8_t so_country_c;
   uint8_t so_market_c;
   uint8_t adjusted_c;
   uint8_t spinoff_c;
   uint8_t is_adjust_same_series_c;
   uint8_t price_info_prev_day_c;
   char no_of_shares_issued_op_c;
   char free_float_op_c;
   uint16_t items_n;
   char filler_2_s [2];
   struct	
   {	
      series_t series;
      int32_t contract_share_i;
      int32_t amount_ratio_i;
   } delivery_change [20];
} answer_underlying_adjustment_item_t;


typedef struct answer_updated_pos_info_item
{
   pos_info_update_api_t pos_info_update_api;
} answer_updated_pos_info_item_t;


typedef struct answer_user_type_info_item
{
   transaction_type_t transaction_type;
   uint8_t trans_or_bdx_c;
   char filler_3_s [3];
} answer_user_type_info_item_t;


typedef struct answer_valuation_group_item
{
   int32_t vag_limit_i;
   char valuation_group_id_s [12];
   char description_s [40];
} answer_valuation_group_item_t;


typedef struct average_price_trade_item
{
   int32_t trade_number_i;
} average_price_trade_item_t;


typedef struct block_order_response_item
{
   int32_t transaction_status_i;
   int32_t trans_ack_i;
   uint8_t item_number_c;
   char filler_3_s [3];
} block_order_response_item_t;


typedef struct block_order_trans_item
{
   series_t series;
   order_var_t order_var;
   int64_t total_volume_i;
} block_order_trans_item_t;


typedef struct block_order_trans_p_item
{
   series_t series;
   order_var_t order_var;
   int64_t total_volume_i;
} block_order_trans_p_item_t;


typedef struct block_price_trans_item
{
   series_t series;
   quad_word order_number_bid_u;
   quad_word order_number_ask_u;
   int32_t bid_premium_i;
   int32_t ask_premium_i;
   int64_t bid_quantity_i;
   int64_t ask_quantity_i;
   int64_t bid_total_volume_i;
   int64_t ask_total_volume_i;
   uint32_t block_n;
   uint16_t time_validity_n;
   uint8_t order_type_c;
   char ex_client_s [16];
   uint8_t delta_quantity_c;
} block_price_trans_item_t;


typedef struct block_price_trans_p_item
{
   series_t series;
   quad_word order_number_bid_u;
   quad_word order_number_ask_u;
   int32_t bid_premium_i;
   int32_t ask_premium_i;
   int64_t bid_quantity_i;
   int64_t ask_quantity_i;
   int64_t bid_total_volume_i;
   int64_t ask_total_volume_i;
   uint32_t block_n;
   uint16_t time_validity_n;
   uint8_t order_type_c;
   char ex_client_s [16];
   uint8_t delta_quantity_c;
} block_price_trans_p_item_t;


typedef struct collateral_base
{
   account_t account;
   series_t series;
   int64_t amount_q;
   char passthrough_s [32];
   char effective_date_s [8];
   char name_s [32];
   char effective_until_s [8];
} collateral_base_t;


typedef struct da28
{
   char central_group_s [12];
   uint16_t segment_number_n;
   uint16_t items_n;
   struct	
   {	
      char long_ins_id_s [32];
      uint16_t leg_number_n;
      uint8_t sort_type_c;
      char filler_1_s;
   } item [30];
} da28_t;


typedef struct clearing_message_item
{
   char text_line_s [80];
} clearing_message_item_t;


typedef struct base_collateral_account
{
   char country_id_s [2];
   char ex_customer_s [5];
   char account_id_s [16];
   char filler_1_s;
} base_collateral_account_t;


typedef struct pos_account
{
   char country_id_s [2];
   char ex_customer_s [5];
   char account_id_s [16];
   char filler_1_s;
} pos_account_t;


typedef struct orig_series
{
   uint8_t country_c;
   uint8_t market_c;
   uint8_t instrument_group_c;
   uint8_t modifier_c;
   uint16_t commodity_n;
   uint16_t expiration_date_n;
   int32_t strike_price_i;
} orig_series_t;


typedef struct match_id
{
   uint64_t execution_event_nbr_u;
   uint32_t match_group_nbr_u;
   uint32_t match_item_nbr_u;
} match_id_t;


typedef struct countersign_code
{
   char country_id_s [2];
   char ex_customer_s [5];
   char user_id_s [5];
} countersign_code_t;


typedef struct margin_account
{
   char country_id_s [2];
   char ex_customer_s [5];
   char account_id_s [16];
   char filler_1_s;
} margin_account_t;


typedef struct currency
{
   uint8_t country_c;
   uint8_t market_c;
   uint8_t instrument_group_c;
   uint8_t modifier_c;
   uint16_t commodity_n;
   uint16_t expiration_date_n;
   int32_t strike_price_i;
} currency_t;


typedef struct combo_series_multi_update_bu1005_item
{
   uint16_t chg_type_n;
   char filler_2_s [2];
   da5_t da5;
} combo_series_multi_update_bu1005_item_t;


typedef struct combo_trade_report_trans_item
{
   series_t series;
   int64_t mp_quantity_i;
   int32_t premium_i;
   uint32_t block_n;
   char settlement_date_s [8];
   char time_of_agreement_date_s [8];
   char time_of_agreement_time_s [6];
   uint8_t deferred_publication_c;
   char filler_1_s;
   trd_rpt_cust_t bid_side;
   trd_rpt_cust_t ask_side;
} combo_trade_report_trans_item_t;


typedef struct confirm_give_up_request_item
{
   account_t account;
   int64_t trade_quantity_i;
   uint8_t open_close_req_c;
   char customer_info_s [15];
} confirm_give_up_request_item_t;


typedef struct corp_action_update_bu53_item
{
   da53_t da53;
} corp_action_update_bu53_item_t;


typedef struct create_acc_access_type_item
{
   account_t account;
} create_acc_access_type_item_t;


typedef struct create_currency_ranking_connections_item
{
   account_t account;
} create_currency_ranking_connections_item_t;


/*   TRANSACTION TYPE = CA129  */
/*   NAMED STRUCT = 102  */

typedef struct currency_ranking_key
{
   participant_t participant;
   char currency_ranking_id_s [32];
   int32_t version_i;
   char filler_4_s [4];
} currency_ranking_key_t;


typedef struct currency_ranking_item
{
   series_t currency_series;
   uint16_t currency_rank_n;
   char filler_2_s [2];
   int64_t cash_collateral_limit_q;
   int64_t direct_credit_limit_q;
} currency_ranking_item_t;


typedef struct delete_currency_ranking_connections_item
{
   account_t account;
   participant_t participant;
   char currency_ranking_id_s [32];
   int32_t version_i;
} delete_currency_ranking_connections_item_t;


typedef struct whose
{
   trading_code_t trading_code;
   char ex_client_s [16];
} whose_t;


typedef struct deposit_withdraw_transfer_collateral_txn_item
{
   deposit_withdraw_collateral_ssi_t deposit_withdraw_collateral_ssi;
} deposit_withdraw_transfer_collateral_txn_item_t;


typedef struct directed_quote_request_ack_item
{
   party_t party;
} directed_quote_request_ack_item_t;


typedef struct directed_quote_request_trans_item
{
   party_t party;
} directed_quote_request_trans_item_t;


typedef struct directed_quote_request_trans_p_item
{
   party_t party;
} directed_quote_request_trans_p_item_t;


typedef struct equil_price_update_item
{
   series_t series;
   int64_t equilibrium_quantity_i;
   int32_t equilibrium_price_i;
   int32_t best_bid_premium_i;
   int32_t best_ask_premium_i;
   int64_t best_bid_quantity_i;
   int64_t best_ask_quantity_i;
   uint8_t matching_price_type_c;
   char filler_3_s [3];
} equil_price_update_item_t;


typedef struct etpr_delta_limit_change_item
{
   series_t series;
   delta_limits_t delta_limits;
} etpr_delta_limit_change_item_t;


typedef struct etpr_limit_change_item
{
   series_t series;
   int32_t upper_limit_i;
   int32_t lower_limit_i;
   int32_t reference_premium_i;
   char filler_4_s [4];
} etpr_limit_change_item_t;


typedef struct da78
{
   series_t series;
   char date_exception_s [8];
} da78_t;


typedef struct da47
{
   series_t series;
   char description_s [40];
   uint32_t haircut_rate_u;
   uint32_t time_to_maturity_u;
} da47_t;


typedef struct instrument_status_info_item
{
   series_t series;
   uint16_t seconds_to_state_change_n;
   uint16_t state_number_n;
   char warning_msg_s [80];
   uint16_t state_level_e;
   char actual_start_date_s [8];
   char actual_start_time_s [6];
   char next_planned_start_date_s [8];
   char next_planned_start_time_s [6];
   char filler_2_s [2];
} instrument_status_info_item_t;


typedef struct da10_da20
{
   series_t series;
   upper_level_series_t upper_level_series;
   int32_t price_quot_factor_i;
   int32_t contract_size_i;
   int32_t exerc_limit_i;
   int32_t redemption_value_i;
   int32_t min_qty_increment_i;
   uint16_t derivate_level_n;
   uint16_t dec_in_strike_price_n;
   uint16_t dec_in_contr_size_n;
   uint16_t rnt_id_n;
   uint16_t dec_in_premium_n;
   uint16_t items_n;
   struct	
   {	
      tick_size_t tick_size;
   } item [12];
   uint16_t dec_in_deliv_n;
   uint16_t items_block_n;
   struct	
   {	
      int64_t maximum_size_u;
      uint32_t minimum_size_n;
      uint32_t block_n;
      uint8_t lot_type_c;
      char filler_3_s [3];
   } block_size [4];
   uint16_t cleared_dec_in_qty_n;
   uint16_t virt_commodity_n;
   uint16_t dec_in_fixing_n;
   char base_cur_s [3];
   uint8_t traded_c;
   uint8_t exerc_limit_unit_c;
   char inc_id_s [14];
   char trc_id_s [10];
   char name_s [32];
   char is_fractions_c;
   uint8_t price_unit_premium_c;
   uint8_t price_unit_strike_c;
   char settl_cur_id_s [32];
   char credit_class_s [3];
   char csd_id_s [12];
   uint8_t trd_cur_unit_c;
   uint8_t collateral_type_c;
   uint8_t fixing_req_c;
   char mbs_id_s [2];
   char valuation_group_id_s [12];
   uint8_t gross_settlement_c;
   char filler_1_s;
} da10_da20_t;


typedef struct irs_leg
{
   int32_t fixed_interest_rate_i;
   series_t float_rate_index;
   int32_t spread_i;
   int32_t init_interest_rate_i;
   char first_rollover_date_s [8];
   uint8_t day_count_conv_c;
   uint8_t rollover_period_c;
   uint8_t rollover_day_c;
   uint8_t fixed_or_float_c;
   party_t party_pay;
   char effective_date_s [8];
   char filler_4_s [4];
} irs_leg_t;


typedef struct limit_change_item
{
   series_t series;
   int32_t upper_limit_i;
   int32_t lower_limit_i;
   int32_t reference_premium_i;
   uint16_t price_source_rule_n;
   char filler_2_s [2];
} limit_change_item_t;


typedef struct stop_series
{
   uint8_t country_c;
   uint8_t market_c;
   uint8_t instrument_group_c;
   uint8_t modifier_c;
   uint16_t commodity_n;
   uint16_t expiration_date_n;
   int32_t strike_price_i;
} stop_series_t;


/*   TRANSACTION TYPE = BO25, BO5, MA476, MA92, MO1, MO3  */
/*   NAMED STRUCT = 34844  */

typedef struct stp_key
{
   uint16_t stp_key_i;
   char filler_2_s [2];
} stp_key_t;


typedef struct mass_quote_trans_item
{
   series_t series;
   int32_t buy_price_i;
   int64_t buy_quantity_u;
   int32_t sell_price_i;
   int64_t sell_quantity_u;
} mass_quote_trans_item_t;


typedef struct mass_quote_update_item
{
   series_t series;
   int32_t buy_price_i;
   int64_t buy_quantity_u;
   int32_t sell_price_i;
   int64_t sell_quantity_u;
} mass_quote_update_item_t;


typedef struct message_information_item
{
   char text_line_s [80];
} message_information_item_t;


typedef struct da87
{
   int64_t quantity_protection_q;
   int64_t delta_protection_q;
   int32_t exposure_time_interval_i;
   int32_t frozen_time_i;
   uint16_t commodity_n;
   char country_id_s [2];
   char ex_customer_s [5];
   uint8_t include_futures_c;
   char filler_2_s [2];
} da87_t;


typedef struct auth_section
{
   uint64_t auth_id;
   char login_user_s [32];
   uint8_t auth_reject_status_c;
   char filler_3_s [3];
} auth_section_t;


typedef struct account_data_external
{
   account_t account;
   countersign_t countersign;
   prop_trade_account_t prop_trade_account;
   prop_deliv_account_t prop_deliv_account;
   prop_pos_account_t prop_pos_account;
   prop_margin_account_t prop_margin_account;
   sink_account_t sink_account;
   prop_origin_account_t prop_origin_account;
   prop_call_account_t prop_call_account;
   int64_t member_exposure_limit_q;
   int32_t rank_class_i;
   char risk_currency_s [3];
   char modified_date_s [8];
   char modified_time_s [6];
   char created_date_s [8];
   char created_time_s [6];
   char investor_type_s [4];
   char nationality_s [4];
   char account_text_s [20];
   char ext_acc_id_s [34];
   char ext_acc_controller_s [15];
   char ext_acc_registrar_s [12];
   char org_number_s [16];
   char account_alias_s [32];
   char diary_number_s [15];
   char acc_type_s [12];
   char fee_type_s [12];
   char cust_bank_id_s [12];
   uint8_t acc_state_c;
   uint8_t read_access_c;
   uint8_t auto_net_c;
   uint8_t risk_cur_conv_c;
   uint8_t risk_margin_net_c;
   uint8_t acc_allow_nov_c;
   uint8_t allow_partial_settlement_c;
   uint8_t cash_collateral_interest_c;
   uint8_t dd_in_base_c;
} account_data_external_t;


typedef struct modify_acc_access_type_item
{
   account_t account;
} modify_acc_access_type_item_t;


typedef struct modify_commission_item
{
   series_t series;
   party_t party;
   char account_id_s [16];
   char customer_info_s [15];
   char created_date_s [8];
   char created_time_s [6];
   char user_code_s [12];
   char filler_3_s [3];
   int32_t commission_i;
} modify_commission_item_t;


typedef struct da18
{
   uint8_t country_c;
   uint8_t market_c;
   char date_non_trading_s [8];
   uint8_t closed_for_trading_c;
   uint8_t closed_for_settlement_c;
   uint8_t closed_for_clearing_c;
   char filler_3_s [3];
} da18_t;


typedef struct da50
{
   series_t series;
   char date_non_trading_s [8];
} da50_t;


typedef struct changes
{
   uint32_t sequence_number_u;
   uint32_t ob_position_u;
   int64_t quantity_difference_i;
   uint8_t ob_command_c;
   uint8_t change_reason_c;
   uint8_t combo_mark_c;
   uint8_t mbo_flags_c;
} changes_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34903  */

typedef struct order_change_separate
{
   series_t series;
   quad_word order_number_u;
   int64_t mp_quantity_i;
   int64_t total_volume_i;
   uint8_t bid_or_ask_c;
   uint8_t change_reason_c;
   char ex_client_s [16];
   char customer_info_s [15];
   char filler_3_s [3];
   originator_trading_code_t originator_trading_code;
   time_spec_t execution_timestamp;
} order_change_separate_t;


typedef struct payment
{
   party_t paying_member;
   char settlement_date_s [8];
   int64_t amount_q;
   series_t currency;
} payment_t;


typedef struct auth_by_whom
{
   trading_code_t trading_code;
   char name_s [32];
} auth_by_whom_t;


typedef struct position_closeout_item
{
   account_t account;
   series_t series;
   int64_t final_held_q;
   int64_t closeout_qty_i;
   char date_s [8];
} position_closeout_item_t;


typedef struct position_closeout_status_item
{
   account_t account;
   series_t series;
   int64_t final_held_q;
   int64_t closeout_qty_i;
   int32_t closeout_status_i;
   char date_s [8];
} position_closeout_status_item_t;


/*   TRANSACTION TYPE = CA132  */
/*   NAMED STRUCT = 105  */

typedef struct acc_access_type_key
{
   participant_t participant;
   char acc_access_type_s [64];
} acc_access_type_key_t;


typedef struct search_series
{
   uint8_t country_c;
   uint8_t market_c;
   uint8_t instrument_group_c;
   uint8_t modifier_c;
   uint16_t commodity_n;
   uint16_t expiration_date_n;
   int32_t strike_price_i;
} search_series_t;


typedef struct query_collateral_transaction_item
{
   uint8_t collateral_transaction_state_c;
} query_collateral_transaction_item_t;


typedef struct query_settlement_instruction_item
{
   uint8_t le_state_c;
} query_settlement_instruction_item_t;


typedef struct other_series
{
   uint8_t country_c;
   uint8_t market_c;
   uint8_t instrument_group_c;
   uint8_t modifier_c;
   uint16_t commodity_n;
   uint16_t expiration_date_n;
   int32_t strike_price_i;
} other_series_t;


typedef struct rectify_deal_item
{
   int32_t trade_number_i;
   int64_t trade_quantity_i;
   uint8_t bid_or_ask_c;
   char reserved_1_c;
   char reserved_2_s [2];
} rectify_deal_item_t;


typedef struct rectify_trade_item
{
   account_t account;
   int64_t trade_quantity_i;
   uint8_t open_close_req_c;
   char customer_info_s [15];
} rectify_trade_item_t;


typedef struct store_account
{
   account_t account;
   countersign_t countersign;
   prop_trade_account_t prop_trade_account;
   prop_settlement_account_t prop_settlement_account;
   prop_delivery_account_t prop_delivery_account;
   prop_pos_account_t prop_pos_account;
   prop_margin_account_t prop_margin_account;
   sink_account_t sink_account;
   prop_origin_account_t prop_origin_account;
   prop_call_account_t prop_call_account;
   cash_opt_account_t cash_opt_account;
   char diary_number_s [15];
   char acc_type_s [12];
   char fee_type_s [12];
   char cust_bank_id_s [12];
   char risk_cur_id_s [3];
   char base_cur_id_s [3];
   char investor_type_s [4];
   char nationality_s [4];
   char account_text_s [20];
   char ext_acc_id_s [34];
   char ext_acc_controller_s [15];
   char ext_acc_registrar_s [12];
   char org_number_s [16];
   char account_alias_s [32];
   uint8_t acc_state_c;
   uint8_t read_access_c;
   uint8_t auto_net_c;
   uint8_t foreign_holder_c;
   uint8_t risk_cur_conv_c;
   uint8_t margin_net_c;
   uint8_t account_collateral_handling_c;
   char filler_3_s [3];
} store_account_t;


typedef struct series_bo_multi_update_bu1009_item
{
   uint16_t chg_type_n;
   char filler_2_s [2];
   da9_t da9;
} series_bo_multi_update_bu1009_item_t;


typedef struct series_multi_update_bu1002_item
{
   uint16_t chg_type_n;
   char filler_2_s [2];
   da2_t da2;
} series_multi_update_bu1002_item_t;


typedef struct settle_price_update_item
{
   series_t series;
   int32_t settle_price_i;
   char settlement_date_s [8];
   uint8_t settlement_price_type_c;
   char date_and_time_s [14];
   char filler_1_s;
} settle_price_update_item_t;


typedef struct set_delta_limit_trans_item
{
   series_t series;
   ref_delta_limits_t ref_delta_limits;
   last_delta_limits_t last_delta_limits;
} set_delta_limit_trans_item_t;


typedef struct bid_side
{
   trd_rpt_part_t trd_rpt_part;
} bid_side_t;


typedef struct ask_side
{
   trd_rpt_part_t trd_rpt_part;
} ask_side_t;


typedef struct da4_da19
{
   int32_t subscription_price_i;
   int32_t interest_rate_i;
   uint16_t commodity_n;
   char com_id_s [6];
   char isin_code_s [12];
   uint16_t dec_in_price_n;
   char date_release_s [8];
   char date_termination_s [8];
   char date_dated_s [8];
   char name_s [32];
   char base_cur_s [3];
   uint8_t deliverable_c;
   uint16_t coupon_frequency_n;
   int64_t nominal_value_q;
   uint16_t day_count_n;
   uint16_t days_in_interest_year_n;
   uint32_t coupon_interest_i;
   uint16_t coupon_settlement_days_n;
   uint8_t underlying_type_c;
   uint8_t price_unit_c;
   uint16_t dec_in_nominal_n;
   uint16_t state_number_n;
   uint16_t linked_commodity_n;
   uint8_t fixed_income_type_c;
   uint8_t underlying_status_c;
   char underlying_issuer_s [6];
   char time_delivery_start_s [6];
   char time_delivery_stop_s [6];
   char sector_code_s [4];
   uint16_t items_n;
   struct	
   {	
      char date_coupdiv_s [8];
      uint32_t dividend_i;
   } coupon [80];
   uint8_t virtual_c;
   char member_circ_numb_s [4];
   char inv_scheme_c;
   char date_closing_s [8];
   char date_last_s [8];
   char country_id_s [2];
   uint8_t cur_unit_c;
   char filler_3_s [3];
} da4_da19_t;


/*   NAMED STRUCT = 18096  */

typedef struct withdraw_collateral_mwa_ssi
{
   account_t account;
   int64_t ssi_id_q;
   int64_t remaining_collateral_amount_q;
   char isin_code_s [12];
   char clh_account_id_s [32];
   char passthrough_s [32];
   char instr_ref_s [16];
   char reason_s [80];
   char currency_s [3];
   uint8_t cm_sim_remaining_type_c;
   uint16_t dec_in_remaining_amount_n;
   uint16_t dec_in_amount_n;
   uint8_t collateral_transaction_state_c;
   uint8_t collateral_transaction_type_c;
   char filler_2_s [2];
} withdraw_collateral_mwa_ssi_t;


/*   TRANSACTION TYPE = CC91, CC92  */
/*   NAMED STRUCT = 76  */

typedef struct aat_participant_connection
{
   participant_t aat_participant;
   participant_t participant;
   char acc_access_type_s [64];
   char created_date_s [8];
   char created_time_s [6];
   char modified_date_s [8];
   char modified_time_s [6];
   uint8_t le_state_c;
   char filler_3_s [3];
   trading_code_t trading_code;
} aat_participant_connection_t;


/*   TRANSACTION TYPE = CC91, CC92  */
/*   NAMED STRUCT = 57  */

typedef struct aat_report_connection
{
   char report_name_s [64];
   participant_t participant;
   char acc_access_type_s [64];
   char created_date_s [8];
   char created_time_s [6];
   char modified_date_s [8];
   char modified_time_s [6];
   uint8_t le_state_c;
   char filler_3_s [3];
   trading_code_t trading_code;
} aat_report_connection_t;


/*   TRANSACTION TYPE = CR97  */

typedef struct aat_rg_connection_status
{
   transaction_type_t transaction_type;
   uint16_t items_n;
   uint8_t connect_type_c;
   char filler_1_s;
   participant_t participant;
   char acc_access_type_s [64];
   aat_rg_connection_status_item_t item [2250];
} aat_rg_connection_status_t;


/*   TRANSACTION TYPE = CC91, CC92  */
/*   NAMED STRUCT = 55  */

typedef struct aat_user_connection
{
   char username_s [32];
   participant_t participant;
   char acc_access_type_s [64];
   char created_date_s [8];
   char created_time_s [6];
   char modified_date_s [8];
   char modified_time_s [6];
   uint8_t le_state_c;
   char filler_3_s [3];
   trading_code_t trading_code;
} aat_user_connection_t;


/*   TRANSACTION TYPE = KC5  */

typedef struct accept_reject_trade_report_for_clearing
{
   transaction_type_t transaction_type;
   series_t series;
   uint64_t trade_report_nbr_q;
   char name_s [32];
   uint8_t confirm_reject_c;
   char filler_3_s [3];
} accept_reject_trade_report_for_clearing_t;


/*   BROADCAST TYPE = BU13  */

typedef struct account_fee_type_update_bu13
{
   broadcast_type_t broadcast_type;
   uint16_t chg_type_n;
   char filler_2_s [2];
   da13_t da13;
} account_fee_type_update_bu13_t;


/*   TRANSACTION TYPE = CA42  */

typedef struct account_status
{
   transaction_type_t transaction_type;
   account_t account;
   uint16_t items_n;
   char filler_2_s [2];
   account_status_item_t item [201];
} account_status_t;


/*   BROADCAST TYPE = BU12  */

typedef struct account_type_update_bu12
{
   broadcast_type_t broadcast_type;
   uint16_t chg_type_n;
   char filler_2_s [2];
   da12_t da12;
} account_type_update_bu12_t;


/*   TRANSACTION TYPE = JA1, JA55, JB2  */
/*   NAMED STRUCT = 50005  */

typedef struct account_vim
{
   account_t account;
} account_vim_t;


/*   TRANSACTION TYPE = CA132  */
/*   NAMED STRUCT = 106  */

typedef struct acc_access_type_attributes
{
   char desc_long_s [128];
   int32_t allow_all_account_i;
   int32_t version_i;
   char created_date_s [8];
   char created_time_s [6];
   char modified_date_s [8];
   char modified_time_s [6];
   uint8_t le_state_c;
   char filler_3_s [3];
} acc_access_type_attributes_t;


/*   TRANSACTION TYPE = CA132  */
/*   NAMED STRUCT = 107  */

typedef struct acc_access_type_itm
{
   account_t account;
   char created_date_s [8];
   char created_time_s [6];
   char modified_date_s [8];
   char modified_time_s [6];
   uint8_t le_state_c;
   char filler_3_s [3];
   trading_code_t trading_code;
} acc_access_type_itm_t;


/*   TRANSACTION TYPE = DC3  */

typedef struct add_tm_combo
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t no_of_legs_n;
   char filler_2_s [2];
   add_tm_combo_item_t item [4];
} add_tm_combo_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34009  */

typedef struct alter_trans
{
   transaction_type_t transaction_type;
   series_t series;
   quad_word order_number_u;
   order_var_t order_var;
} alter_trans_t;


/*   TRANSACTION TYPE = CC15  */

typedef struct annul_exercise_req
{
   transaction_type_t transaction_type;
   series_t series;
   int32_t exercise_number_i;
} annul_exercise_req_t;


/*   TRANSACTION TYPE = CA117  */
/*   NAMED STRUCT = 54  */

typedef struct answer_aat_connection
{
   participant_t participant;
   char acc_access_type_s [64];
   char username_s [32];
   int32_t version_i;
   char created_date_s [8];
   char created_time_s [6];
   char modified_date_s [8];
   char modified_time_s [6];
   uint8_t le_state_c;
   char filler_3_s [3];
   trading_code_t trading_code;
} answer_aat_connection_t;


/*   TRANSACTION TYPE = CA117  */
/*   NAMED STRUCT = 77  */

typedef struct answer_aat_connection_participant
{
   participant_t participant;
   char acc_access_type_s [64];
   participant_t aat_participant;
   int32_t version_i;
   char created_date_s [8];
   char created_time_s [6];
   char modified_date_s [8];
   char modified_time_s [6];
   uint8_t le_state_c;
   char filler_3_s [3];
   trading_code_t trading_code;
} answer_aat_connection_participant_t;


/*   TRANSACTION TYPE = CA117  */
/*   NAMED STRUCT = 56  */

typedef struct answer_aat_connection_report
{
   participant_t participant;
   char acc_access_type_s [64];
   char report_name_s [64];
   int32_t version_i;
   char created_date_s [8];
   char created_time_s [6];
   char modified_date_s [8];
   char modified_time_s [6];
   uint8_t le_state_c;
   char filler_3_s [3];
   trading_code_t trading_code;
} answer_aat_connection_report_t;


/*   TRANSACTION TYPE = CA117  */
/*   NAMED STRUCT = 79  */

typedef struct answer_aat_connection_risk_group
{
   participant_t participant;
   char acc_access_type_s [64];
   int32_t version_i;
   char created_date_s [8];
   char created_time_s [6];
   char modified_date_s [8];
   char modified_time_s [6];
   uint8_t le_state_c;
   char filler_3_s [3];
   trading_code_t trading_code;
} answer_aat_connection_risk_group_t;


/*   TRANSACTION TYPE = CA38  */

typedef struct answer_account_ext
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_account_ext_item_t item [133];
} answer_account_ext_t;


/*   TRANSACTION TYPE = DA13  */

typedef struct answer_account_fee_type
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_account_fee_type_item_t item [100];
} answer_account_fee_type_t;


/*   TRANSACTION TYPE = CA128  */

typedef struct answer_account_hdr
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
} answer_account_hdr_t;


/*   TRANSACTION TYPE = DA12  */

typedef struct answer_account_type
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_account_type_item_t item [100];
} answer_account_type_t;


/*   TRANSACTION TYPE = DA34  */

typedef struct answer_account_type_rule
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_account_type_rule_item_t item [100];
} answer_account_type_rule_t;


/*   TRANSACTION TYPE = CA116  */

typedef struct answer_acc_access_type
{
   transaction_type_t transaction_type;
   uint16_t items_n;
   uint16_t segment_number_n;
   participant_t participant;
   char acc_access_type_s [64];
   char desc_long_s [128];
   int32_t allow_all_account_i;
   int32_t version_i;
   char created_date_s [8];
   char created_time_s [6];
   char modified_date_s [8];
   char modified_time_s [6];
   uint8_t le_state_c;
   char filler_3_s [3];
   answer_acc_access_type_item_t item [900];
} answer_acc_access_type_t;


/*   TRANSACTION TYPE = CA53  */

typedef struct answer_api_delivery
{
   transaction_type_t transaction_type;
   series_t series;
   char from_date_s [8];
   int32_t sequence_first_i;
   uint16_t items_n;
   char filler_2_s [2];
   answer_api_delivery_item_t item [280];
} answer_api_delivery_t;


/*   TRANSACTION TYPE = CA77  */

typedef struct answer_api_give_up
{
   transaction_type_t transaction_type;
   series_t series;
   char from_date_s [8];
   int32_t sequence_first_i;
   uint16_t items_n;
   char filler_2_s [2];
   answer_api_give_up_item_t item [300];
} answer_api_give_up_t;


/*   TRANSACTION TYPE = CA11  */

typedef struct answer_api_trade_hdr
{
   transaction_type_t transaction_type;
   series_t series;
   char from_date_s [8];
   int32_t sequence_first_i;
   uint16_t items_n;
   char filler_2_s [2];
} answer_api_trade_hdr_t;


/*   TRANSACTION TYPE = DA58  */

typedef struct answer_authorized_report
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_authorized_report_item_t item [200];
} answer_authorized_report_t;


/*   TRANSACTION TYPE = CA36  */

typedef struct answer_average_price_trade
{
   transaction_type_t transaction_type;
   series_t series;
   partition_low_t partition_low;
   partition_high_t partition_high;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_average_price_trade_item_t item [1000];
} answer_average_price_trade_t;


/*   TRANSACTION TYPE = UA10, UA22  */

typedef struct answer_bi26_signals_sent
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_bi26_signals_sent_item_t item [1000];
} answer_bi26_signals_sent_t;


/*   TRANSACTION TYPE = UA13  */

typedef struct answer_bi27_broadcasts_sent
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   char filler_1_s;
   uint8_t items_c;
   answer_bi27_broadcasts_sent_item1_t item1 [50];
} answer_bi27_broadcasts_sent_t;


/*   TRANSACTION TYPE = UA20  */

typedef struct answer_bi73_signals_sent
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_bi73_signals_sent_item_t item [1000];
} answer_bi73_signals_sent_t;


/*   TRANSACTION TYPE = UA21, UA9  */

typedef struct answer_bi7_signals_sent
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_bi7_signals_sent_item_t item [1000];
} answer_bi7_signals_sent_t;


/*   TRANSACTION TYPE = MA99  */

typedef struct answer_block_size
{
   transaction_type_t transaction_type;
   int32_t max_block_order_size_i;
   int32_t max_block_price_size_i;
} answer_block_size_t;


/*   TRANSACTION TYPE = DA6  */

typedef struct answer_broker
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   char country_id_s [2];
   char ex_customer_s [5];
   char filler_1_s;
   uint16_t items_n;
   answer_broker_item_t item [50];
} answer_broker_t;


/*   TRANSACTION TYPE = UA12  */

typedef struct answer_business_date
{
   transaction_type_t transaction_type;
   char omex_version_s [16];
   char business_date_s [8];
   char utc_date_s [8];
   char utc_time_s [6];
   char tz_variable_s [40];
   char filler_2_s [2];
   int32_t utc_offset_i;
} answer_business_date_t;


/*   TRANSACTION TYPE = DA28  */

typedef struct answer_central_group
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_central_group_item_t item [1000];
} answer_central_group_t;


/*   TRANSACTION TYPE = CA68  */

typedef struct answer_clearing_date
{
   transaction_type_t transaction_type;
   partition_low_t partition_low;
   partition_high_t partition_high;
   char omex_version_s [16];
   char business_date_s [8];
   uint16_t items_n;
   char filler_2_s [2];
   answer_clearing_date_item_t item [1500];
} answer_clearing_date_t;


/*   TRANSACTION TYPE = CA123  */

typedef struct answer_closeout_log
{
   transaction_type_t transaction_type;
   partition_low_t partition_low;
   partition_high_t partition_high;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_closeout_log_item_t item [799];
} answer_closeout_log_t;


/*   TRANSACTION TYPE = FA1, FA14, FA15, FA16, FA17, FA19, FA2  */

typedef struct answer_collateral
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
} answer_collateral_t;


/*   TRANSACTION TYPE = DA5, DA77  */

typedef struct answer_combo
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint8_t items_c;
   char filler_1_s;
   answer_combo_item_t item [100];
} answer_combo_t;


/*   TRANSACTION TYPE = CA64  */

typedef struct answer_commission
{
   transaction_type_t transaction_type;
   party_t party;
   uint8_t send_receive_c;
   char filler_1_s;
   uint16_t items_n;
   answer_commission_item_t item [760];
} answer_commission_t;


/*   TRANSACTION TYPE = CA62  */

typedef struct answer_conf_give_up_req_items
{
   transaction_type_t transaction_type;
   uint16_t items_n;
   char filler_2_s [2];
   answer_conf_give_up_req_items_item_t item [50];
} answer_conf_give_up_req_items_t;


/*   TRANSACTION TYPE = DA15  */

typedef struct answer_converted_series
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_converted_series_item_t item [100];
} answer_converted_series_t;


/*   TRANSACTION TYPE = MA59  */

typedef struct answer_cool_off_period_ended
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t items_n;
   char filler_2_s [2];
   answer_cool_off_period_ended_item_t item [1000];
} answer_cool_off_period_ended_t;


/*   TRANSACTION TYPE = DA53  */

typedef struct answer_corp_action_da53
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_corp_action_da53_item_t item [1000];
} answer_corp_action_da53_t;


/*   TRANSACTION TYPE = DI95  */

typedef struct answer_create_flexible_deriv
{
   transaction_type_t transaction_type;
   series_t series;
} answer_create_flexible_deriv_t;


/*   TRANSACTION TYPE = DA33  */

typedef struct answer_currency
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_currency_item_t item [100];
} answer_currency_t;


/*   TRANSACTION TYPE = CA130, CA131  */

typedef struct answer_currency_ranking_connections
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_currency_ranking_connections_item_t item [500];
} answer_currency_ranking_connections_t;


/*   TRANSACTION TYPE = DA46  */

typedef struct answer_deal_source
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_deal_source_item_t item [100];
} answer_deal_source_t;


/*   TRANSACTION TYPE = CA31  */

typedef struct answer_delivery
{
   transaction_type_t transaction_type;
   partition_low_t partition_low;
   partition_high_t partition_high;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_delivery_item_t item [100];
} answer_delivery_t;


/*   TRANSACTION TYPE = MA2153  */

typedef struct answer_delta_limit
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t items_n;
   char filler_2_s [2];
   answer_delta_limit_item_t item [1000];
} answer_delta_limit_t;


/*   TRANSACTION TYPE = JA31  */

typedef struct answer_dh_margin_components
{
   transaction_type_t transaction_type;
   char business_date_s [8];
   char margin_time_s [6];
   char filler_2_s [2];
   int32_t sequence_number_n;
   uint16_t segment_number_n;
   uint16_t items_n;
   uint16_t size_n;
   uint8_t run_type_c;
   char filler_1_s;
} answer_dh_margin_components_t;


/*   TRANSACTION TYPE = JA31  */
/*   NAMED STRUCT = 21134  */

typedef struct answer_dh_margin_components_item
{
   account_t account;
   int64_t scanning_risk_q;
   int64_t inter_month_spread_charge_q;
   int64_t delivery_charge_q;
   int64_t dh_inter_com_spread_credit_q;
   int64_t short_option_minimum_charge_q;
   int64_t premium_margin_q;
   int64_t opt_premium_margin_q;
   int64_t var_margin_q;
   char cco_id_s [6];
   char currency_s [3];
   uint8_t risk_type_used_c;
   char filler_6_s [6];
} answer_dh_margin_components_item_t;


/*   TRANSACTION TYPE = CA22  */

typedef struct answer_error_msg
{
   transaction_type_t transaction_type;
   partition_low_t partition_low;
   partition_high_t partition_high;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_error_msg_item_t item [100];
} answer_error_msg_t;


/*   TRANSACTION TYPE = MA2156  */

typedef struct answer_etpr_delta_limit
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t items_n;
   char filler_2_s [2];
   answer_etpr_delta_limit_item_t item [1000];
} answer_etpr_delta_limit_t;


/*   TRANSACTION TYPE = DA78  */

typedef struct answer_exception_days
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_exception_days_item_t item [500];
} answer_exception_days_t;


/*   TRANSACTION TYPE = DA24  */

typedef struct answer_exchange_da24
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_exchange_da24_item_t item [100];
} answer_exchange_da24_t;


/*   TRANSACTION TYPE = RA31  */

typedef struct answer_exchange_rate
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_exchange_rate_item_t item [500];
} answer_exchange_rate_t;


/*   TRANSACTION TYPE = CA21  */

typedef struct answer_exercise_req
{
   transaction_type_t transaction_type;
   partition_low_t partition_low;
   partition_high_t partition_high;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_exercise_req_item_t item [250];
} answer_exercise_req_t;


/*   TRANSACTION TYPE = CA100  */

typedef struct answer_fixing_dates
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t items_n;
   char filler_2_s [2];
   answer_fixing_dates_item_t item [50];
} answer_fixing_dates_t;


/*   TRANSACTION TYPE = CA8  */

typedef struct answer_fixing_val
{
   transaction_type_t transaction_type;
   partition_low_t partition_low;
   partition_high_t partition_high;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_fixing_val_item_t item [500];
} answer_fixing_val_t;


/*   TRANSACTION TYPE = CA61  */

typedef struct answer_give_up_request
{
   transaction_type_t transaction_type;
   partition_low_t partition_low;
   partition_high_t partition_high;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_give_up_request_item_t item [410];
} answer_give_up_request_t;


/*   TRANSACTION TYPE = RA36  */

typedef struct answer_greeks
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   uint16_t marg_run_nbr_n;
   uint16_t marg_call_nbr_n;
   char created_date_s [8];
   char created_time_s [6];
   char filler_6_s [6];
   answer_greeks_item_t item [1500];
} answer_greeks_t;


/*   TRANSACTION TYPE = DA47  */

typedef struct answer_haircut
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_haircut_item_t item [500];
} answer_haircut_t;


/*   TRANSACTION TYPE = IA21, IA22  */

typedef struct answer_hdr
{
   transaction_type_t transaction_type;
   uint16_t items_n;
   uint16_t size_n;
} answer_hdr_t;


/*   TRANSACTION TYPE = DA22, DA3  */

typedef struct answer_instrument
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_instrument_item_t item [100];
} answer_instrument_t;


/*   TRANSACTION TYPE = DA10, DA20  */

typedef struct answer_instrument_class
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_instrument_class_item_t item [145];
} answer_instrument_class_t;


/*   TRANSACTION TYPE = DA8  */

typedef struct answer_instrument_group
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_instrument_group_item_t item [100];
} answer_instrument_group_t;


/*   TRANSACTION TYPE = UA15  */

typedef struct answer_instrument_status
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_instrument_status_item_t item [1000];
} answer_instrument_status_t;


/*   TRANSACTION TYPE = MA1  */

typedef struct answer_limit
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t items_n;
   char filler_2_s [2];
   answer_limit_item_t item [1000];
} answer_limit_t;


/*   TRANSACTION TYPE = LA3  */

typedef struct answer_list_ver
{
   transaction_type_t transaction_type;
   series_t series;
   int32_t info_type_i;
   uint16_t segment_number_n;
   char list_name_s [40];
   char report_version_s [3];
   char filler_1_s;
   char file_type_s [8];
   uint16_t items_n;
   char text_buffer_s [50000];
} answer_list_ver_t;


/*   TRANSACTION TYPE = LA5  */

typedef struct answer_list_ver_nrs
{
   transaction_type_t transaction_type;
   uint16_t buffer_length_n;
   uint16_t segment_number_n;
   char file_name_s [80];
   int32_t report_no_i;
   char country_id_s [2];
   char ex_customer_s [5];
   char report_spec_s [5];
   char clh_id_s [12];
   char business_date_s [8];
   char report_version_s [3];
   uint8_t ascii_bin_c;
   uint8_t data_buffer_s [61440];
} answer_list_ver_nrs_t;


/*   TRANSACTION TYPE = SA2  */

typedef struct answer_manual_payments
{
   transaction_type_t transaction_type;
   partition_low_t partition_low;
   partition_high_t partition_high;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_manual_payments_item_t item [250];
} answer_manual_payments_t;


/*   TRANSACTION TYPE = JA9  */
/*   NAMED STRUCT = 21123  */

typedef struct answer_marginable_spread_status
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   uint16_t rejected_items_n;
} answer_marginable_spread_status_t;


/*   TRANSACTION TYPE = JA9  */
/*   NAMED STRUCT = 21124  */

typedef struct answer_marginable_spread_status_item
{
   account_t account;
   series_t series;
   uint8_t spread_status_c;
   char filler_3_s [3];
} answer_marginable_spread_status_item_t;


/*   TRANSACTION TYPE = RA21  */

typedef struct answer_margin_acc
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_margin_acc_item_t item [500];
} answer_margin_acc_t;


/*   TRANSACTION TYPE = RA35  */

typedef struct answer_margin_data_used
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   uint16_t marg_run_nbr_n;
   uint16_t marg_call_nbr_n;
   char created_date_s [8];
   char created_time_s [6];
   char filler_6_s [6];
   answer_margin_data_used_item_t item [600];
} answer_margin_data_used_t;


/*   TRANSACTION TYPE = RA7  */

typedef struct answer_margin_detail
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   uint16_t marg_run_nbr_n;
   uint16_t marg_call_nbr_n;
   char created_date_s [8];
   char created_time_s [6];
   char filler_6_s [6];
   answer_margin_detail_item_t item [430];
} answer_margin_detail_t;


/*   TRANSACTION TYPE = RA6  */

typedef struct answer_margin_ext
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_margin_ext_item_t item [500];
} answer_margin_ext_t;


/*   TRANSACTION TYPE = RA23  */

typedef struct answer_margin_mem
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_margin_mem_item_t item [500];
} answer_margin_mem_t;


/*   TRANSACTION TYPE = RA20  */

typedef struct answer_margin_pa_acc
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_margin_pa_acc_item_t item [500];
} answer_margin_pa_acc_t;


/*   TRANSACTION TYPE = RA122, RA22  */

typedef struct answer_margin_prop
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   uint16_t marg_run_nbr_n;
   uint16_t marg_call_nbr_n;
   char created_date_s [8];
   char created_time_s [6];
   char filler_6_s [6];
   answer_margin_prop_item_t item [400];
} answer_margin_prop_t;


/*   TRANSACTION TYPE = JA54, JA55  */

typedef struct answer_margin_requirement_account
{
   transaction_type_t transaction_type;
   char business_date_s [8];
   char margin_time_s [6];
   char filler_2_s [2];
   int32_t sequence_number_n;
   uint16_t segment_number_n;
   uint16_t items_n;
   uint16_t size_n;
   uint8_t run_type_c;
   uint8_t incl_t_plus_one_prices_c;
   collection_id_t price_collection_id;
} answer_margin_requirement_account_t;


/*   TRANSACTION TYPE = JA7  */

typedef struct answer_margin_results_internal
{
   transaction_type_t transaction_type;
   partition_low_t partition_low;
   partition_high_t partition_high;
   int32_t sequence_number_n;
   uint16_t segment_number_n;
   uint16_t items_n;
   uint16_t size_n;
   char filler_2_s [2];
} answer_margin_results_internal_t;


/*   TRANSACTION TYPE = RA1  */

typedef struct answer_margin_series_param
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_margin_series_param_item_t item [500];
} answer_margin_series_param_t;


/*   TRANSACTION TYPE = RA3  */

typedef struct answer_margin_series_param_ext
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   uint16_t marg_run_nbr_n;
   uint16_t marg_call_nbr_n;
   char created_date_s [8];
   char created_time_s [6];
   char filler_6_s [6];
   answer_margin_series_param_ext_item_t item [500];
} answer_margin_series_param_ext_t;


/*   TRANSACTION TYPE = RA41  */

typedef struct answer_margin_ulg_price
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_margin_ulg_price_item_t item [300];
} answer_margin_ulg_price_t;


/*   TRANSACTION TYPE = JA1  */

typedef struct answer_marg_calc_runs
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   char business_date_s [8];
   uint16_t items_n;
   uint16_t size_n;
} answer_marg_calc_runs_t;


/*   TRANSACTION TYPE = RA72  */

typedef struct answer_marg_sim_add_trade
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_marg_sim_add_trade_item_t item [1000];
} answer_marg_sim_add_trade_t;


/*   TRANSACTION TYPE = DA23, DA7  */

typedef struct answer_market
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_market_item_t item [100];
} answer_market_t;


/*   TRANSACTION TYPE = DA57  */

typedef struct answer_member_obligation_da57
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_member_obligation_da57_item_t item [500];
} answer_member_obligation_da57_t;


/*   TRANSACTION TYPE = CA52  */

typedef struct answer_missing_delivery
{
   transaction_type_t transaction_type;
   char filler_2_s [2];
   uint16_t items_n;
   answer_missing_delivery_item_t item [280];
} answer_missing_delivery_t;


/*   TRANSACTION TYPE = CA76  */

typedef struct answer_missing_give_up
{
   transaction_type_t transaction_type;
   uint16_t items_n;
   char filler_2_s [2];
   answer_missing_give_up_item_t item [300];
} answer_missing_give_up_t;


/*   TRANSACTION TYPE = CA39  */

typedef struct answer_missing_trade_change
{
   transaction_type_t transaction_type;
   char filler_2_s [2];
   uint16_t items_n;
   answer_missing_trade_change_item_t item [1000];
} answer_missing_trade_change_t;


/*   TRANSACTION TYPE = CA10  */

typedef struct answer_missing_trade_hdr
{
   transaction_type_t transaction_type;
   char filler_2_s [2];
   uint16_t items_n;
} answer_missing_trade_hdr_t;


/*   TRANSACTION TYPE = DA87  */

typedef struct answer_mm_protection
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_mm_protection_item_t item [500];
} answer_mm_protection_t;


/*   TRANSACTION TYPE = TA70, TA71  */

typedef struct answer_next_series_hdr
{
   transaction_type_t transaction_type;
   series_t next_series;
   uint16_t segment_number_n;
   uint16_t items_n;
   uint16_t size_n;
   char filler_2_s [2];
} answer_next_series_hdr_t;


/*   TRANSACTION TYPE = DA18  */

typedef struct answer_non_trading_days
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_non_trading_days_item_t item [100];
} answer_non_trading_days_t;


/*   TRANSACTION TYPE = DA50  */

typedef struct answer_non_trad_settl_days
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_non_trad_settl_days_item_t item [100];
} answer_non_trad_settl_days_t;


/*   TRANSACTION TYPE = CA20  */

typedef struct answer_open_interest
{
   transaction_type_t transaction_type;
   partition_low_t partition_low;
   partition_high_t partition_high;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_open_interest_item_t item [1000];
} answer_open_interest_t;


/*   TRANSACTION TYPE = CA72  */

typedef struct answer_open_interest_ext
{
   transaction_type_t transaction_type;
   partition_low_t partition_low;
   partition_high_t partition_high;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_open_interest_ext_item_t item [1000];
} answer_open_interest_ext_t;


/*   TRANSACTION TYPE = MA476, MA92  */

typedef struct answer_order_hdr
{
   transaction_type_t transaction_type;
   series_t next_series;
   quad_word next_order_number_u;
   uint8_t bid_or_ask_c;
   char filler_3_s [3];
   uint16_t items_n;
   uint16_t size_n;
} answer_order_hdr_t;


/*   TRANSACTION TYPE = UA1  */

typedef struct answer_partition
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_partition_item_t item [100];
} answer_partition_t;


/*   TRANSACTION TYPE = SA1  */

typedef struct answer_paynote_info
{
   transaction_type_t transaction_type;
   partition_low_t partition_low;
   partition_high_t partition_high;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_paynote_info_item_t item [250];
} answer_paynote_info_t;


/*   TRANSACTION TYPE = CA3, CA65  */

typedef struct answer_position
{
   transaction_type_t transaction_type;
   partition_low_t partition_low;
   partition_high_t partition_high;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_position_item_t item [500];
} answer_position_t;


/*   TRANSACTION TYPE = CA122  */

typedef struct answer_position_history
{
   transaction_type_t transaction_type;
   partition_low_t partition_low;
   partition_high_t partition_high;
   series_t series;
   account_t account;
   int64_t nbr_held_q;
   int64_t nbr_written_q;
   int64_t qty_closed_out_q;
   char date_s [8];
} answer_position_history_t;


/*   TRANSACTION TYPE = IA17  */

typedef struct answer_prel_settlement
{
   transaction_type_t transaction_type;
   uint16_t items_n;
   uint16_t segment_number_n;
   answer_prel_settlement_item_t item [1500];
} answer_prel_settlement_t;


/*   TRANSACTION TYPE = MA58  */

typedef struct answer_price_limit_trigger
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t items_n;
   char filler_2_s [2];
   answer_price_limit_trigger_item_t item [1000];
} answer_price_limit_trigger_t;


/*   TRANSACTION TYPE = CA19  */

typedef struct answer_propagate
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_propagate_item_t item [100];
} answer_propagate_t;


/*   TRANSACTION TYPE = RA44  */

typedef struct answer_realtime_ulg_price
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_realtime_ulg_price_item_t item [300];
} answer_realtime_ulg_price_t;


/*   TRANSACTION TYPE = CA16  */

typedef struct answer_rectify_d
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   char reserved_2_s [2];
   partition_low_t partition_low;
   partition_high_t partition_high;
   uint16_t items_n;
   char filler_2_s [2];
   answer_rectify_d_item_t item [100];
} answer_rectify_d_t;


/*   TRANSACTION TYPE = CA17  */

typedef struct answer_rectify_d_cont
{
   transaction_type_t transaction_type;
   uint16_t items_n;
   char filler_2_s [2];
   answer_rectify_d_cont_item_t item [255];
} answer_rectify_d_cont_t;


/*   TRANSACTION TYPE = CA15  */

typedef struct answer_rectify_ext_cont
{
   transaction_type_t transaction_type;
   uint16_t items_n;
   char filler_2_s [2];
   answer_rectify_ext_cont_item_t item [100];
} answer_rectify_ext_cont_t;


/*   TRANSACTION TYPE = CA14  */

typedef struct answer_rectify_t
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   char reserved_2_s [2];
   partition_low_t partition_low;
   partition_high_t partition_high;
   uint16_t items_n;
   uint8_t instance_next_c;
   char filler_1_s;
   answer_rectify_t_item_t item [400];
} answer_rectify_t_t;


/*   TRANSACTION TYPE = LA6  */

typedef struct answer_report_nrs
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_report_nrs_item_t item [351];
} answer_report_nrs_t;


/*   TRANSACTION TYPE = LA4  */

typedef struct answer_report_ver
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_report_ver_item_t item [450];
} answer_report_ver_t;


/*   TRANSACTION TYPE = JA21, JA277  */

typedef struct answer_risk_margin_scaling_factor
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   char business_date_s [8];
   uint16_t items_n;
   uint16_t size_n;
} answer_risk_margin_scaling_factor_t;


/*   TRANSACTION TYPE = JA71  */

typedef struct answer_rm_margin_sim
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t segment_number_out_n;
   uint16_t items_n;
   uint16_t size_n;
} answer_rm_margin_sim_t;


/*   TRANSACTION TYPE = JA10  */

typedef struct answer_rm_param_obj
{
   transaction_type_t transaction_type;
   int32_t sequence_number_n;
   char margin_date_s [8];
   char margin_time_s [6];
   uint8_t run_type_c;
   char filler_1_s;
   uint16_t segment_number_n;
   uint16_t items_n;
   uint16_t size_n;
   char filler_2_s [2];
} answer_rm_param_obj_t;


/*   TRANSACTION TYPE = DA120, DA121, DA122, DA123, DA124, DA125, DA126, DA130, DA131, DA134, DA136, DA90, FA20, FA21, FA22, FA24, FA29, FA40, UA14  */

typedef struct answer_segment_hdr
{
   transaction_type_t transaction_type;
   uint16_t items_n;
   uint16_t size_n;
   uint16_t segment_number_n;
   char filler_2_s [2];
} answer_segment_hdr_t;


/*   TRANSACTION TYPE = CA117, CA129, CA132  */

typedef struct answer_seg_hdr
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
} answer_seg_hdr_t;


/*   TRANSACTION TYPE = DA2  */

typedef struct answer_series
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_series_item_t item [300];
} answer_series_t;


/*   TRANSACTION TYPE = DA9  */

typedef struct answer_series_bo
{
   transaction_type_t transaction_type;
   char date_trading_s [8];
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_series_bo_item_t item [330];
} answer_series_bo_t;


/*   TRANSACTION TYPE = DA76  */

typedef struct answer_state_type
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_state_type_item_t item [100];
} answer_state_type_t;


/*   TRANSACTION TYPE = IB12  */

typedef struct answer_tot_equil_prices
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint8_t instance_c;
   uint8_t instance_next_c;
   series_next_t series_next;
   uint16_t items_n;
   char filler_2_s [2];
   answer_tot_equil_prices_item_t item [1230];
} answer_tot_equil_prices_t;


/*   TRANSACTION TYPE = MA42  */

typedef struct answer_tot_ob
{
   transaction_type_t transaction_type;
   series_t series;
   quad_word order_number_u;
   uint16_t items_n;
   uint8_t bid_or_ask_c;
   char filler_1_s;
   answer_tot_ob_item_t item [994];
} answer_tot_ob_t;


/*   TRANSACTION TYPE = MA8  */

typedef struct answer_tot_order
{
   transaction_type_t transaction_type;
   series_t series;
   uint32_t order_index_u;
   uint16_t items_n;
   char filler_2_s [2];
   answer_tot_order_item_t item [283];
} answer_tot_order_t;


/*   TRANSACTION TYPE = KA1  */

typedef struct answer_trade_report
{
   transaction_type_t transaction_type;
   partition_low_t partition_low;
   partition_high_t partition_high;
   uint16_t segment_number_n;
   uint16_t items_n;
} answer_trade_report_t;


/*   TRANSACTION TYPE = DA45  */

typedef struct answer_trade_report_types
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_trade_report_types_item_t item [200];
} answer_trade_report_types_t;


/*   TRANSACTION TYPE = IA42  */

typedef struct answer_trade_statistics
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_trade_statistics_item_t item [500];
} answer_trade_statistics_t;


/*   TRANSACTION TYPE = DA29  */

typedef struct answer_trading_state
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_trading_state_item_t item [100];
} answer_trading_state_t;


/*   TRANSACTION TYPE = MA78  */

typedef struct answer_trd_report
{
   transaction_type_t transaction_type;
   series_t series;
   uint32_t order_index_u;
   uint16_t items_n;
   char filler_2_s [2];
   answer_trd_report_item_t item [300];
} answer_trd_report_t;


/*   TRANSACTION TYPE = MA80  */

typedef struct answer_trd_report_party
{
   transaction_type_t transaction_type;
   series_t series;
   quad_word order_number_u;
   uint16_t items_n;
   uint8_t bid_or_ask_c;
   char filler_1_s;
   answer_trd_report_party_item_t item [300];
} answer_trd_report_party_t;


/*   TRANSACTION TYPE = DA19, DA4  */

typedef struct answer_underlying
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_underlying_item_t item [50];
} answer_underlying_t;


/*   TRANSACTION TYPE = DA14  */

typedef struct answer_underlying_adjustment
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_underlying_adjustment_item_t item [100];
} answer_underlying_adjustment_t;


/*   TRANSACTION TYPE = CA40  */

typedef struct answer_updated_pos_info
{
   transaction_type_t transaction_type;
   partition_low_t partition_low;
   partition_high_t partition_high;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_updated_pos_info_item_t item [888];
} answer_updated_pos_info_t;


/*   TRANSACTION TYPE = JA11  */

typedef struct answer_used_marg_params
{
   transaction_type_t transaction_type;
   int32_t sequence_number_n;
   char margin_date_s [8];
   char margin_time_s [6];
   uint8_t run_type_c;
   char filler_1_s;
   uint16_t segment_number_n;
   uint16_t items_n;
   uint16_t size_n;
   char filler_2_s [2];
} answer_used_marg_params_t;


/*   TRANSACTION TYPE = DA30  */

typedef struct answer_user_type_info
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   char ust_id_s [5];
   uint8_t ext_or_int_c;
   uint8_t is_trader_c;
   uint8_t program_trader_c;
   uint8_t trader_authorization_c;
   uint8_t hide_firm_order_trade_c;
   char filler_2_s [2];
   answer_user_type_info_item_t item [100];
} answer_user_type_info_t;


/*   TRANSACTION TYPE = DA132  */

typedef struct answer_valuation_group
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   answer_valuation_group_item_t item [100];
} answer_valuation_group_t;


/*   TRANSACTION TYPE = UI1  */

typedef struct application_status
{
   transaction_type_t transaction_type;
   series_t series;
   int32_t application_status_i;
} application_status_t;


/*   TRANSACTION TYPE = CD32  */

typedef struct average_price_trade
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t items_n;
   char filler_2_s [2];
   average_price_trade_item_t item [1000];
} average_price_trade_t;


/*   TRANSACTION TYPE = FA16  */
/*   NAMED STRUCT = 18043  */

typedef struct base_call
{
   int64_t base_collateral_req_q;
   int64_t adjusted_base_collateral_req_q;
} base_call_t;


/*   TRANSACTION TYPE = BO25, BO5, MO1, MO385  */
/*   NAMED STRUCT = 34810  */

typedef struct basic_order
{
   int32_t premium_i;
   int64_t quantity_i;
   uint32_t block_n;
   uint16_t time_validity_n;
   uint16_t exch_order_type_n;
   uint8_t order_type_c;
   uint8_t bid_or_ask_c;
   char filler_2_s [2];
} basic_order_t;


/*   TRANSACTION TYPE = MA476, MA92  */
/*   NAMED STRUCT = 34817  */

typedef struct basic_order_book_order
{
   series_t series;
   trading_code_t owner;
   give_up_member_t give_up_member;
   quad_word order_number_u;
   time_spec_t timestamp_in;
   time_spec_t timestamp_created;
   uint32_t sequence_number_u;
   uint32_t ob_position_u;
   int32_t premium_i;
   int64_t quantity_i;
   int64_t original_quantity_i;
   uint32_t block_n;
   uint16_t time_validity_n;
   uint16_t exch_order_type_n;
   uint16_t transaction_number_n;
   char exchange_info_s [32];
   char customer_info_s [15];
   char ex_client_s [16];
   uint8_t open_close_req_c;
   uint8_t order_type_c;
   uint8_t bid_or_ask_c;
   uint8_t change_reason_c;
   char filler_3_s [3];
} basic_order_book_order_t;


/*   TRANSACTION TYPE = BO25, BO5, MO3, MO387  */
/*   NAMED STRUCT = 34815  */

typedef struct basic_order_update
{
   int32_t premium_i;
   int64_t quantity_i;
   int64_t balance_quantity_i;
   uint16_t time_validity_n;
   uint16_t exch_order_type_n;
   uint8_t delta_quantity_c;
   char filler_3_s [3];
} basic_order_update_t;


/*   TRANSACTION TYPE = BD70, BD71, TA70, TA71  */
/*   NAMED STRUCT = 34401  */

typedef struct basic_trade_ticker
{
   series_t series;
   time_spec_t timestamp_match;
   time_spec_t time_of_publication;
   uint64_t execution_event_nbr_u;
   uint32_t match_group_nbr_u;
   int64_t deal_quantity_i;
   int32_t deal_price_i;
   uint16_t segment_number_n;
   uint8_t aggressive;
   char filler_1_s;
} basic_trade_ticker_t;


/*   TRANSACTION TYPE = CB146  */

typedef struct bdx_cl_otc_trade_op_on_hold
{
   broadcast_type_t broadcast_type;
   uint16_t items_n;
   uint16_t size_n;
} bdx_cl_otc_trade_op_on_hold_t;


/*   TRANSACTION TYPE = JB1, JB2  */

typedef struct bdx_marg_calc_runs
{
   broadcast_type_t broadcast_type;
   char business_date_s [8];
   uint16_t items_n;
   uint16_t size_n;
} bdx_marg_calc_runs_t;


/*   TRANSACTION TYPE = BI84  */
/*   NAMED STRUCT = 35006  */

typedef struct bi84_bdx_info
{
   char business_date_s [8];
   uint32_t sequence_number_u;
   char sent_date_s [8];
   char sent_time_s [6];
   user_code_t user_code;
   char clh_id_s [12];
   char host_name_s [32];
   uint8_t event_status_i;
   char filler_1_s;
} bi84_bdx_info_t;


/*   BROADCAST TYPE = BO99  */

typedef struct block_order_response
{
   broadcast_type_t broadcast_type;
   quad_word order_number_u;
   uint8_t items_c;
   char filler_3_s [3];
   block_order_response_item_t item [100];
} block_order_response_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34006  */

typedef struct block_order_trans
{
   transaction_type_t transaction_type;
   series_t series;
   give_up_member_t give_up_member;
   char exchange_info_s [32];
   uint8_t items_c;
   char filler_3_s [3];
   block_order_trans_item_t item [100];
} block_order_trans_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34106  */

typedef struct block_order_trans_p
{
   transaction_type_t transaction_type;
   series_t series;
   trading_code_t trading_code;
   give_up_member_t give_up_member;
   char exchange_info_s [32];
   uint8_t items_c;
   char filler_3_s [3];
   block_order_trans_p_item_t item [100];
} block_order_trans_p_t;


/*   TRANSACTION TYPE = BO25, BO5, MO36  */
/*   NAMED STRUCT = 34007  */

typedef struct block_price_trans
{
   transaction_type_t transaction_type;
   series_t series;
   give_up_member_t give_up_member;
   char exchange_info_s [32];
   char customer_info_s [15];
   uint8_t items_c;
   uint16_t stp_key_i;
   char filler_2_s [2];
   block_price_trans_item_t item [14];
} block_price_trans_t;


/*   TRANSACTION TYPE = BO25, BO5, MO420  */
/*   NAMED STRUCT = 34107  */

typedef struct block_price_trans_p
{
   transaction_type_t transaction_type;
   series_t series;
   trading_code_t trading_code;
   give_up_member_t give_up_member;
   char exchange_info_s [32];
   char customer_info_s [15];
   uint8_t items_c;
   uint16_t stp_key_i;
   char filler_2_s [2];
   block_price_trans_p_item_t item [14];
} block_price_trans_p_t;


/*   TRANSACTION TYPE = DC96  */

typedef struct block_unblock_ptlg
{
   transaction_type_t transaction_type;
   series_t series;
   char ptl_id_s [80];
   uint8_t ptl_blocked_c;
   char filler_3_s [3];
} block_unblock_ptlg_t;


/*   TRANSACTION TYPE = BD2, BD6, BD70, BD71, BI81, BI84, BO16, BO17, BO25, BO5, BO55, CB31, FB17, FB18, FB6, KB10, KB14  */

typedef struct broadcast_hdr
{
   broadcast_type_t broadcast_type;
   uint16_t items_n;
   uint16_t size_n;
} broadcast_hdr_t;


/*   TRANSACTION TYPE = BU120, BU121, BU122, BU123, BU124, BU125, BU126, BU134, BU136, BU90  */

typedef struct broadcast_segment_hdr
{
   broadcast_type_t broadcast_type;
   uint16_t items_n;
   uint16_t size_n;
   uint16_t segment_number_n;
   char filler_2_s [2];
} broadcast_segment_hdr_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34013  */

typedef struct broker_trans
{
   transaction_type_t transaction_type;
   series_t series;
   order_var_t order_var;
   party_t party;
   char exchange_info_s [32];
} broker_trans_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34113  */

typedef struct broker_trans_p
{
   transaction_type_t transaction_type;
   series_t series;
   trading_code_t trading_code;
   order_var_t order_var;
   party_t party;
   char exchange_info_s [32];
} broker_trans_p_t;


/*   TRANSACTION TYPE = KC2  */

typedef struct cancel_trade_report
{
   transaction_type_t transaction_type;
   series_t series;
   uint64_t trade_report_nbr_q;
   char name_s [32];
   uint8_t confirm_reject_c;
   char filler_3_s [3];
} cancel_trade_report_t;


/*   TRANSACTION TYPE = FA1, FA2, FB1  */
/*   NAMED STRUCT = 18003  */

typedef struct cash_collateral
{
   collateral_base_t collateral_base;
} cash_collateral_t;


/*   BROADCAST TYPE = BU28  */

typedef struct central_group_update
{
   broadcast_type_t broadcast_type;
   uint16_t chg_type_n;
   char filler_2_s [2];
   da28_t da28;
} central_group_update_t;


/*   TRANSACTION TYPE = CC45  */

typedef struct change_account_state
{
   transaction_type_t transaction_type;
   series_t series;
   account_t account;
   uint8_t acc_state_c;
   char filler_3_s [3];
} change_account_state_t;


/*   TRANSACTION TYPE = FA29  */
/*   NAMED STRUCT = 18075  */

typedef struct clearing_house_account_light
{
   char clh_account_id_s [32];
   char clh_id_s [12];
   char bank_name_s [50];
   char bic_code_s [15];
   char account_number_s [34];
   char account_name_s [50];
   char filler_3_s [3];
} clearing_house_account_light_t;


/*   TRANSACTION TYPE = BO25, BO5, MO1, MO3, MO385, MO387  */
/*   NAMED STRUCT = 34802  */

typedef struct clearing_info
{
   give_up_member_t give_up_member;
   char ex_client_s [16];
   uint8_t open_close_req_c;
   char filler_1_s;
} clearing_info_t;


/*   BROADCAST TYPE = BI27  */

typedef struct clearing_message
{
   broadcast_type_t broadcast_type;
   uint16_t broadcast_number_n;
   char yyyymmdd_s [8];
   char hhmmss_s [6];
   uint8_t country_c;
   uint8_t market_c;
   uint16_t items_n;
   clearing_message_item_t item [10];
} clearing_message_t;


/*   TRANSACTION TYPE = CA128, CB31  */
/*   NAMED STRUCT = 81  */

typedef struct cl_account_base_api
{
   account_t account;
   countersign_t countersign;
   prop_trade_account_t prop_trade_account;
   prop_settlement_account_t prop_settlement_account;
   prop_pos_account_t prop_pos_account;
   prop_margin_account_t prop_margin_account;
   sink_account_t sink_account;
   prop_origin_account_t prop_origin_account;
   prop_call_account_t prop_call_account;
   prop_delivery_account_t prop_delivery_account;
   int64_t member_exposure_limit_q;
   char modified_date_s [8];
   char modified_time_s [6];
   char created_date_s [8];
   char created_time_s [6];
   char investor_type_s [4];
   char nationality_s [4];
   char account_text_s [20];
   char org_number_s [16];
   char account_alias_s [32];
   char diary_number_s [15];
   char acc_type_s [12];
   char fee_type_s [12];
   char cust_bank_id_s [12];
   uint8_t acc_state_c;
   uint8_t read_access_c;
   uint8_t auto_net_c;
   uint8_t acc_allow_nov_c;
   uint8_t auto_take_up_c;
   uint8_t foreign_holder_c;
   char filler_3_s [3];
} cl_account_base_api_t;


/*   TRANSACTION TYPE = CA128, CB31  */
/*   NAMED STRUCT = 94  */

typedef struct cl_account_base_collateral_api
{
   base_collateral_account_t base_collateral_account;
   int32_t bc_adjustment_factor_i;
} cl_account_base_collateral_api_t;


/*   TRANSACTION TYPE = CA128, CB31  */
/*   NAMED STRUCT = 86  */

typedef struct cl_account_collateral_attribute_api
{
   cash_opt_account_t cash_opt_account;
   char base_cur_id_s [3];
   uint8_t account_collateral_handling_c;
   uint8_t cash_collateral_interest_c;
   uint8_t dd_in_base_c;
   char filler_2_s [2];
} cl_account_collateral_attribute_api_t;


/*   TRANSACTION TYPE = CA128, CB31  */
/*   NAMED STRUCT = 97  */

typedef struct cl_account_intraday_funding_api
{
   account_t intraday_funding_account;
} cl_account_intraday_funding_api_t;


/*   TRANSACTION TYPE = CA128, CB31  */
/*   NAMED STRUCT = 93  */

typedef struct cl_account_non_ccp_margin_api
{
   account_t prop_non_ccp_margin_account;
} cl_account_non_ccp_margin_api_t;


/*   TRANSACTION TYPE = CA128, CB31  */
/*   NAMED STRUCT = 82  */

typedef struct cl_account_risk_attribute_api
{
   int32_t rank_class_i;
   char risk_currency_s [3];
   uint8_t risk_cur_conv_c;
   uint8_t risk_margin_net_c;
   char margin_class_s [3];
   char risk_scale_s [12];
} cl_account_risk_attribute_api_t;


/*   TRANSACTION TYPE = CA128, CB31  */
/*   NAMED STRUCT = 100  */

typedef struct cl_account_settlement_attribute_api
{
   uint8_t allow_partial_settlement_c;
   char filler_3_s [3];
} cl_account_settlement_attribute_api_t;


/*   TRANSACTION TYPE = CB146  */
/*   NAMED STRUCT = 95  */

typedef struct cl_otc_operation_info
{
   uint8_t cl_otc_trade_operation_c;
   uint8_t le_state_c;
   char filler_2_s [2];
   int32_t orig_deal_number_i;
   series_t series;
   int32_t sequence_number_i;
   char created_date_s [8];
   char created_time_s [6];
   char modified_date_s [8];
   char modified_time_s [6];
   int32_t tx_status_i;
   trading_code_t trading_code;
   char business_date_s [8];
} cl_otc_operation_info_t;


/*   TRANSACTION TYPE = CB146  */
/*   NAMED STRUCT = 96  */

typedef struct cl_otc_trade_operation
{
   account_t account;
   pos_account_t pos_account;
   int32_t orig_trade_number_i;
   uint8_t trade_type_c;
   uint8_t trade_report_reason_c;
   uint8_t buy_sell_c;
   char filler_1_s;
   int64_t trade_quantity_i;
   int64_t total_surplus_deficit_q;
} cl_otc_trade_operation_t;


/*   TRANSACTION TYPE = BD6, CA10, CA11  */
/*   NAMED STRUCT = 3  */

typedef struct cl_trade_base_api
{
   trading_code_t trading_code;
   series_t series;
   give_up_member_t give_up_member;
   quad_word order_number_u;
   int32_t sequence_number_i;
   int32_t trade_number_i;
   int32_t deal_price_i;
   int64_t trade_quantity_i;
   account_t account;
   char customer_info_s [15];
   uint8_t bought_or_sold_c;
   uint8_t deal_source_c;
   uint8_t open_close_req_c;
   uint8_t trade_type_c;
   uint8_t le_state_c;
   user_code_t user_code;
   char created_date_s [8];
   char created_time_s [6];
   char asof_date_s [8];
   char asof_time_s [6];
   char modified_date_s [8];
   char modified_time_s [6];
   uint8_t trade_state_c;
   uint8_t attention_c;
   int32_t deal_number_i;
   uint32_t global_deal_no_u;
   int32_t orig_trade_number_i;
   orig_series_t orig_series;
   char exchange_info_s [32];
   uint32_t big_attention_u;
   char clearing_date_s [8];
   time_spec_t execution_timestamp;
   uint8_t trade_venue_c;
   uint8_t instance_c;
   uint16_t exch_order_type_n;
   party_t party;
   uint16_t trade_rep_code_n;
   uint16_t state_number_n;
   match_id_t match_id;
} cl_trade_base_api_t;


/*   TRANSACTION TYPE = BD6, CA10, CA11  */
/*   NAMED STRUCT = 20  */

typedef struct cl_trade_secur_part
{
   countersign_code_t countersign_code;
   new_series_t new_series;
   party_t party;
   pos_account_t pos_account;
   combo_series_t combo_series;
   int64_t nbr_held_q;
   int64_t nbr_written_q;
   int64_t total_held_q;
   int64_t total_written_q;
   int32_t ext_seq_nbr_i;
   int32_t ext_status_i;
   int64_t rem_quantity_i;
   int64_t quantity_i;
   uint32_t ext_trade_number_u;
   uint32_t orig_ext_trade_number_u;
   int32_t residual_i;
   int32_t give_up_number_i;
   int32_t commission_i;
   int32_t combo_deal_price_i;
   char clearing_date_s [8];
   char passthrough_s [32];
   char ex_client_s [16];
   char ext_trade_fee_type_c;
   uint8_t give_up_state_c;
   char reserved_2_s [2];
   uint8_t orig_trade_type_c;
   uint8_t open_close_c;
   char reserved_1_c;
   uint8_t client_category_c;
   uint8_t instigant_c;
   uint8_t cab_price_ind_c;
   char filler_2_s [2];
} cl_trade_secur_part_t;


/*   TRANSACTION TYPE = BD6, CA10, CA11  */
/*   NAMED STRUCT = 67  */

typedef struct cl_trade_trade_report_api
{
   char time_of_agreement_date_s [8];
   char time_of_agreement_time_s [6];
   char filler_2_s [2];
} cl_trade_trade_report_api_t;


/*   TRANSACTION TYPE = CD34  */

typedef struct cl_transfer_position
{
   transaction_type_t transaction_type;
   series_t series;
   account_t account;
   new_account_t new_account;
   int64_t nbr_held_q;
   int64_t nbr_written_q;
   uint8_t open_close_req_c;
   char filler_3_s [3];
   char clearing_date_s [8];
} cl_transfer_position_t;


/*   TRANSACTION TYPE = FA20, FA21, FA22, FA24, FB6  */
/*   NAMED STRUCT = 18095  */

typedef struct cm_collateral_mwa_info
{
   int64_t remaining_collateral_amount_q;
   uint8_t cm_sim_remaining_type_c;
   char filler_3_s [3];
} cm_collateral_mwa_info_t;


/*   TRANSACTION TYPE = FA40  */
/*   NAMED STRUCT = 18090  */

typedef struct cm_collateral_sim_failure_reason
{
   char failure_reason_s [160];
} cm_collateral_sim_failure_reason_t;


/*   TRANSACTION TYPE = FA40  */
/*   NAMED STRUCT = 18092  */

typedef struct cm_collateral_sim_result_sgx
{
   series_t series;
   account_t account;
   int64_t collateral_amount_q;
   uint16_t dec_in_amount_n;
   char filler_2_s [2];
} cm_collateral_sim_result_sgx_t;


/*   TRANSACTION TYPE = FQ40  */
/*   NAMED STRUCT = 18091  */

typedef struct cm_collateral_sim_sgx
{
   series_t series;
   account_t account;
   int64_t remaining_collateral_amount_q;
   char isin_code_s [12];
   char currency_s [3];
   uint8_t cm_sim_remaining_type_c;
   uint16_t dec_in_remaining_amount_n;
   char filler_2_s [2];
} cm_collateral_sim_sgx_t;


/*   TRANSACTION TYPE = FA17, FB17, FB18  */
/*   NAMED STRUCT = 18033  */

typedef struct collateral_evaluation_run_info
{
   account_t account;
   uint32_t request_nbr_u;
   uint32_t margin_sequence_nbr_u;
   char clh_id_s [12];
   char valuation_date_s [8];
   char created_date_s [8];
   char created_time_s [6];
   char margin_date_s [8];
   char clearing_date_s [8];
   char ca_batch_isin_code_s [12];
   uint8_t is_intraday_c;
   uint8_t collateral_state_c;
   uint8_t is_final_c;
   uint8_t collateral_evaluation_type_c;
   uint8_t create_direct_debit_c;
   uint8_t coll_payment_state_c;
   uint8_t intraday_evaluation_c;
   uint8_t collateral_transaction_state_c;
   uint8_t trigger_new_margin_calc_c;
   char filler_1_s;
} collateral_evaluation_run_info_t;


/*   TRANSACTION TYPE = FA16  */
/*   NAMED STRUCT = 18028  */

typedef struct collateral_information_base
{
   margin_account_t margin_account;
   currency_t currency;
   currency_t base_currency;
   int64_t initial_margin_req_q;
   int64_t variation_margin_req_q;
   int64_t contingent_variation_margin_req_q;
   int64_t margin_maintenance_q;
   int64_t margin_extraordinary_q;
   int64_t margin_total_q;
   int64_t collateral_guarantee_q;
   int64_t collateral_cash_q;
   int64_t collateral_security_q;
   int64_t total_surplus_deficit_q;
   int64_t total_margin_req_q;
   int64_t collateral_fixed_income_q;
   int64_t collateral_equity_q;
   int64_t otcf_margin_q;
   int64_t otcf_additional_margin_q;
   int64_t otcf_settlement_variation_q;
   int64_t external_margin_req_q;
   int64_t settlement_requirement_q;
   int64_t collateral_cash_after_settlement_q;
   int64_t additional_margin_req_q;
   int64_t pai_q;
} collateral_information_base_t;


/*   TRANSACTION TYPE = FA16  */
/*   NAMED STRUCT = 18029  */

typedef struct collateral_information_default_fund
{
   int64_t margin_mutual_fund_q;
   int64_t margin_default_fund_q;
} collateral_information_default_fund_t;


/*   TRANSACTION TYPE = FA16  */
/*   NAMED STRUCT = 18057  */

typedef struct collateral_information_payment
{
   int64_t adjusted_collateral_cash_q;
   int64_t cash_collateral_limit_q;
   int64_t settlement_requirement_q;
   int64_t collateral_cash_after_settlement_q;
} collateral_information_payment_t;


/*   TRANSACTION TYPE = FA16  */
/*   NAMED STRUCT = 18030  */

typedef struct collateral_information_payment_delivery
{
   int64_t payment_margin_valuation_date_q;
   int64_t payment_margin_future_date_q;
   int64_t delivery_margin_valuation_date_q;
   int64_t payment_margin_overdue_q;
   int64_t delivery_margin_overdue_q;
} collateral_information_payment_delivery_t;


/*   TRANSACTION TYPE = FA1, FA2, FB1  */
/*   NAMED STRUCT = 18073  */

typedef struct collateral_info_sgx
{
   trading_code_t trading_code;
   user_code_t user_code;
   uint64_t collateral_nbr_q;
   uint16_t version_n;
   char timestamp_date_s [8];
   char timestamp_time_s [6];
   char asof_date_s [8];
   char asof_time_s [6];
   char name_s [32];
   uint8_t collateral_type_c;
   uint8_t state_c;
   int64_t preliminary_amount_q;
   uint16_t dec_in_amount_n;
   char isin_code_s [12];
   uint8_t collateral_series_expired_c;
   char filler_1_s;
} collateral_info_sgx_t;


/*   TRANSACTION TYPE = FA22, FB6  */
/*   NAMED STRUCT = 18056  */

typedef struct collateral_payment_transaction_recon
{
   int64_t total_sum_debit_q;
   int64_t total_sum_credit_q;
   int64_t sum_debit_bank_q;
   int64_t sum_credit_bank_q;
   int64_t sum_debit_internal_transfer_q;
   int64_t sum_credit_internal_transfer_q;
   int64_t sum_debit_cash_settlement_q;
   int64_t sum_credit_cash_settlement_q;
   uint32_t total_nbr_of_debit_u;
   uint32_t total_nbr_of_credit_u;
   uint32_t nbr_of_debit_bank_u;
   uint32_t nbr_of_credit_bank_u;
   uint32_t nbr_of_debit_internal_transfer_u;
   uint32_t nbr_of_credit_internal_transfer_u;
   uint32_t nbr_of_debit_cash_settlement_u;
   uint32_t nbr_of_credit_cash_settlement_u;
   uint32_t request_nbr_u;
   uint16_t dec_in_amount_n;
   char currency_s [3];
   char settlement_date_s [8];
   char instr_ref_s [16];
   uint8_t ext_confirm_c;
   char filler_2_s [2];
} collateral_payment_transaction_recon_t;


/*   TRANSACTION TYPE = FA20, FA21, FA22, FA24, FB6  */
/*   NAMED STRUCT = 18064  */

typedef struct collateral_transaction_base
{
   series_t series;
   account_t collateral_account;
   account_t collateral_account_party;
   int64_t amount_q;
   int64_t gross_amount_q;
   uint64_t collateral_transaction_nbr_q;
   uint32_t instruction_nbr_u;
   uint32_t coll_payment_nbr_u;
   uint32_t ext_coll_payment_nbr_u;
   uint32_t request_nbr_u;
   uint16_t version_n;
   uint16_t dec_in_amount_n;
   char valuation_date_s [8];
   char settlement_date_s [8];
   char isin_code_s [12];
   char instr_ref_s [16];
   char reason_s [80];
   char passthrough_s [64];
   char created_date_s [8];
   char created_time_s [6];
   char modified_date_s [8];
   char modified_time_s [6];
   char settlement_instr_date_s [8];
   char sender_bic_code_s [15];
   char csd_code_s [34];
   char currency_s [3];
   uint8_t ext_confirm_c;
   uint8_t collateral_transaction_type_c;
   uint8_t collateral_transaction_state_c;
   uint8_t released_holding_c;
   uint8_t collateral_type_c;
   char filler_3_s [3];
   char date_termination_s [8];
   uint32_t coupon_interest_i;
} collateral_transaction_base_t;


/*   TRANSACTION TYPE = FA14  */
/*   NAMED STRUCT = 18036  */

typedef struct coll_val_per_series
{
   account_t collateral_account;
   margin_account_t margin_account;
   series_t series;
   currency_t currency;
   int64_t collateral_amount_q;
   int64_t market_value_q;
   int64_t coll_value_ins_cur_before_limit_adjust_q;
   int64_t coll_value_ins_cur_after_limit_adjust_q;
   int64_t ex_rate_q;
   int64_t coll_value_ins_cur_after_ser_limit_adjust_q;
   int32_t collateral_price_i;
   int32_t percentage_after_haircut_i;
   char vag_id_s [12];
   uint16_t dec_in_rate_n;
   uint16_t dec_in_amount_n;
   uint16_t dec_in_collateral_price_n;
   char isin_code_s [12];
   char filler_2_s [2];
   int64_t final_collateral_amount_q;
   int64_t post_collateral_amount_q;
   int64_t post_final_collateral_amount_q;
} coll_val_per_series_t;


/*   TRANSACTION TYPE = FA14  */
/*   NAMED STRUCT = 18025  */

typedef struct coll_val_per_series_base_cur
{
   currency_t base_currency;
   int64_t coll_value_base_curr_before_limit_adjust_q;
   int64_t coll_value_base_curr_after_limit_adjust_q;
   int64_t coll_value_base_cur_after_ser_limit_adjust_q;
   int32_t series_limit_i;
} coll_val_per_series_base_cur_t;


/*   TRANSACTION TYPE = FA14  */
/*   NAMED STRUCT = 18026  */

typedef struct coll_val_per_series_risk_cur
{
   currency_t risk_currency;
   currency_t coll_value_currency;
   int64_t collateral_value_q;
} coll_val_per_series_risk_cur_t;


/*   TRANSACTION TYPE = FA15  */
/*   NAMED STRUCT = 18027  */

typedef struct coll_val_per_val_group_tsn
{
   margin_account_t margin_account;
   currency_t base_currency;
   int64_t coll_value_base_curr_before_limit_ajust_q;
   int64_t coll_value_base_curr_after_limit_adjust_q;
   int64_t coll_value_base_cur_after_ser_limit_adjust_q;
   int32_t group_limit_i;
   int32_t actual_group_percentage_i;
   char vag_id_s [12];
   uint16_t dec_in_actual_group_percentage_n;
   char filler_2_s [2];
} coll_val_per_val_group_tsn_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34016  */

typedef struct combo_acc_trans
{
   transaction_type_t transaction_type;
   series_t series;
   order_var_t order_var;
   char exchange_info_s [32];
   quad_word order_number_u;
   give_up_member_t give_up_member;
} combo_acc_trans_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34116  */

typedef struct combo_acc_trans_p
{
   transaction_type_t transaction_type;
   series_t series;
   trading_code_t trading_code;
   order_var_t order_var;
   char exchange_info_s [32];
   quad_word order_number_u;
   give_up_member_t give_up_member;
} combo_acc_trans_p_t;


/*   BROADCAST TYPE = BU1005  */

typedef struct combo_series_multi_update_bu1005
{
   broadcast_type_t broadcast_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   combo_series_multi_update_bu1005_item_t item [10];
} combo_series_multi_update_bu1005_t;


/*   TRANSACTION TYPE = MO77  */

typedef struct combo_trade_report_trans
{
   transaction_type_t transaction_type;
   series_t series;
   uint8_t ext_t_state_c;
   char filler_1_s;
   uint16_t items_n;
   combo_trade_report_trans_item_t item [6];
} combo_trade_report_trans_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34907  */

typedef struct combo_trans_part
{
   transaction_type_t transaction_type;
   series_t series;
   order_var_t order_var;
   char exchange_info_s [32];
   give_up_member_t give_up_member;
} combo_trans_part_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34908  */

typedef struct combo_trans_part_p
{
   transaction_type_t transaction_type;
   series_t series;
   trading_code_t trading_code;
   order_var_t order_var;
   char exchange_info_s [32];
   give_up_member_t give_up_member;
} combo_trans_part_p_t;


/*   BROADCAST TYPE = BU5, BU77  */

typedef struct combo_update_bu5
{
   broadcast_type_t broadcast_type;
   uint16_t chg_type_n;
   char filler_2_s [2];
   da5_t da5;
} combo_update_bu5_t;


/*   TRANSACTION TYPE = CC38  */

typedef struct confirm_give_up_request
{
   transaction_type_t transaction_type;
   series_t series;
   int32_t give_up_number_i;
   uint16_t items_n;
   char filler_2_s [2];
   confirm_give_up_request_item_t item [50];
} confirm_give_up_request_t;


/*   TRANSACTION TYPE = CC12  */

typedef struct confirm_rectify_d
{
   transaction_type_t transaction_type;
   series_t series;
   int64_t rectify_deal_number_q;
   uint8_t operation_c;
   uint8_t confirm_reject_c;
   char filler_2_s [2];
} confirm_rectify_d_t;


/*   TRANSACTION TYPE = CC11  */

typedef struct confirm_rectify_t
{
   transaction_type_t transaction_type;
   series_t series;
   int32_t rectify_trade_number_i;
   uint8_t confirm_reject_c;
   char filler_3_s [3];
} confirm_rectify_t_t;


/*   BROADCAST TYPE = BL59  */

typedef struct cool_off_period_ended
{
   broadcast_type_t broadcast_type;
   series_t series;
   time_spec_t timestamp;
   int32_t lower_limit_i;
   int32_t upper_limit_i;
   uint8_t cool_off_ended_type_c;
   char price_limit_unit_c;
   char filler_2_s [2];
} cool_off_period_ended_t;


/*   TRANSACTION TYPE = FA20, FA21, FA22, FB6  */
/*   NAMED STRUCT = 18038  */

typedef struct corporate_action_info
{
   char corp_action_ref_s [16];
   char corp_event_ref_s [16];
} corporate_action_info_t;


/*   BROADCAST TYPE = BU53  */

typedef struct corp_action_update_bu53
{
   broadcast_type_t broadcast_type;
   uint16_t chg_type_n;
   uint16_t items_n;
   corp_action_update_bu53_item_t item [50];
} corp_action_update_bu53_t;


/*   TRANSACTION TYPE = CC91  */

typedef struct create_aat_connection_hdr
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t items_n;
   uint8_t connect_type_c;
   char filler_1_s;
   participant_t participant;
   char acc_access_type_s [64];
   int32_t version_i;
} create_aat_connection_hdr_t;


/*   TRANSACTION TYPE = CC97  */

typedef struct create_aat_rg_connection
{
   transaction_type_t transaction_type;
   series_t series;
   uint8_t connect_type_c;
   char filler_3_s [3];
   participant_t participant;
   char acc_access_type_s [64];
} create_aat_rg_connection_t;


/*   TRANSACTION TYPE = CC88  */

typedef struct create_acc_access_type
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t items_n;
   char filler_2_s [2];
   participant_t participant;
   char acc_access_type_s [64];
   char desc_long_s [128];
   int32_t allow_all_account_i;
   int32_t version_i;
   create_acc_access_type_item_t item [2600];
} create_acc_access_type_t;


/*   TRANSACTION TYPE = CC106  */

typedef struct create_currency_ranking_connections
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t items_n;
   char filler_2_s [2];
   participant_t participant;
   char currency_ranking_id_s [32];
   create_currency_ranking_connections_item_t item [1000];
} create_currency_ranking_connections_t;


/*   TRANSACTION TYPE = DC95  */

typedef struct create_flexible_deriv
{
   transaction_type_t transaction_type;
   series_t series;
   char date_expiration_s [8];
   int32_t strike_price_i;
} create_flexible_deriv_t;


/*   TRANSACTION TYPE = CC103, CC104  */

typedef struct currency_ranking
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t items_n;
   char filler_2_s [2];
   currency_ranking_key_t key;
   currency_ranking_item_t item [1000];
} currency_ranking_t;


/*   TRANSACTION TYPE = CA129  */
/*   NAMED STRUCT = 104  */

typedef struct currency_ranking_attributes
{
   char created_date_s [8];
   char created_time_s [6];
   char modified_date_s [8];
   char modified_time_s [6];
   trading_code_t trading_code;
   uint8_t le_state_c;
   char filler_3_s [3];
} currency_ranking_attributes_t;


/*   TRANSACTION TYPE = CA129  */
/*   NAMED STRUCT = 103  */

typedef struct currency_ranking_entry
{
   series_t currency_series;
   uint16_t currency_rank_n;
   char filler_2_s [2];
   int64_t cash_collateral_limit_q;
   int64_t direct_credit_limit_q;
} currency_ranking_entry_t;


/*   TRANSACTION TYPE = FA16  */
/*   NAMED STRUCT = 18049  */

typedef struct deficit_to_cover
{
   int64_t deficit_to_cover_q;
} deficit_to_cover_t;


/*   TRANSACTION TYPE = CC93  */

typedef struct delete_aat_connection
{
   transaction_type_t transaction_type;
   series_t series;
   uint8_t connect_type_c;
   char filler_3_s [3];
   participant_t participant;
   char acc_access_type_s [64];
   int32_t version_i;
} delete_aat_connection_t;


/*   TRANSACTION TYPE = CC90  */

typedef struct delete_acc_access_type
{
   transaction_type_t transaction_type;
   series_t series;
   participant_t participant;
   char acc_access_type_s [64];
   int32_t version_i;
} delete_acc_access_type_t;


/*   TRANSACTION TYPE = CC105  */

typedef struct delete_currency_ranking
{
   transaction_type_t transaction_type;
   series_t series;
   currency_ranking_key_t key;
} delete_currency_ranking_t;


/*   TRANSACTION TYPE = CC107  */

typedef struct delete_currency_ranking_connections
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t items_n;
   char filler_2_s [2];
   delete_currency_ranking_connections_item_t item [500];
} delete_currency_ranking_connections_t;


/*   TRANSACTION TYPE = BO25, BO5, MO4, MO40, MO74  */
/*   NAMED STRUCT = 34011  */

typedef struct delete_trans
{
   transaction_type_t transaction_type;
   series_t series;
   quad_word order_number_u;
   whose_t whose;
   uint8_t bid_or_ask_c;
   char customer_info_s [15];
   char exchange_info_s [32];
} delete_trans_t;


/*   TRANSACTION TYPE = BO25, BO5, MO388, MO424  */
/*   NAMED STRUCT = 34111  */

typedef struct delete_trans_p
{
   transaction_type_t transaction_type;
   series_t series;
   trading_code_t trading_code;
   quad_word order_number_u;
   whose_t whose;
   uint8_t bid_or_ask_c;
   char customer_info_s [15];
   char exchange_info_s [32];
} delete_trans_p_t;


/*   TRANSACTION TYPE = FO20  */

typedef struct deposit_withdraw_collateral_txn
{
   transaction_type_t transaction_type;
   series_t series;
   deposit_withdraw_collateral_ssi_t deposit_withdraw_collateral_ssi;
   char filler_4_s [4];
} deposit_withdraw_collateral_txn_t;


/*   TRANSACTION TYPE = FO22  */

typedef struct deposit_withdraw_transfer_collateral_txn
{
   transaction_type_t transaction_type;
   series_t series;
   char filler_4_s [4];
   deposit_withdraw_transfer_collateral_txn_item_t item [2];
} deposit_withdraw_transfer_collateral_txn_t;


/*   TRANSACTION TYPE = BI81, UA14  */
/*   NAMED STRUCT = 35003  */

typedef struct destination_item
{
   series_t series;
   uint8_t destination_level_c;
   char filler_3_s [3];
} destination_item_t;


/*   TRANSACTION TYPE = FB1  */

typedef struct directed_collateral
{
   broadcast_type_t broadcast_type;
   uint16_t items_n;
   uint16_t size_n;
} directed_collateral_t;


/*   BROADCAST TYPE = BD18  */

typedef struct directed_delivery
{
   broadcast_type_t broadcast_type;
   cl_delivery_api_t cl_delivery_api;
} directed_delivery_t;


/*   BROADCAST TYPE = BD29  */

typedef struct directed_give_up
{
   broadcast_type_t broadcast_type;
   cl_give_up_api_t cl_give_up_api;
} directed_give_up_t;


/*   BROADCAST TYPE = BD40  */

typedef struct directed_pos_info_update
{
   broadcast_type_t broadcast_type;
   pos_info_update_api_t pos_info_update_api;
} directed_pos_info_update_t;


/*   BROADCAST TYPE = BO51  */

typedef struct directed_quote_request
{
   broadcast_type_t broadcast_type;
   series_t series;
   user_code_t user_code;
   quad_word order_number_u;
   time_spec_t timestamp_created;
   int32_t time_to_respond_i;
   int64_t mp_quantity_i;
   uint8_t bid_or_ask_c;
   char filler_3_s [3];
} directed_quote_request_t;


/*   BROADCAST TYPE = BO52  */

typedef struct directed_quote_request_ack
{
   broadcast_type_t broadcast_type;
   series_t series;
   user_code_t user_code;
   quad_word order_number_u;
   time_spec_t timestamp_created;
   int32_t time_to_respond_i;
   int64_t mp_quantity_i;
   ex_user_code_t ex_user_code;
   uint8_t bid_or_ask_c;
   uint8_t items_c;
   uint8_t quote_request_status_c;
   char filler_1_s;
   directed_quote_request_ack_item_t item [100];
} directed_quote_request_ack_t;


/*   TRANSACTION TYPE = MO51  */

typedef struct directed_quote_request_trans
{
   transaction_type_t transaction_type;
   series_t series;
   int64_t mp_quantity_i;
   uint8_t bid_or_ask_c;
   uint8_t items_c;
   char filler_2_s [2];
   directed_quote_request_trans_item_t item [25];
} directed_quote_request_trans_t;


/*   TRANSACTION TYPE = MO435  */

typedef struct directed_quote_request_trans_p
{
   transaction_type_t transaction_type;
   series_t series;
   trading_code_t trading_code;
   int64_t mp_quantity_i;
   uint8_t bid_or_ask_c;
   uint8_t items_c;
   char filler_2_s [2];
   directed_quote_request_trans_p_item_t item [25];
} directed_quote_request_trans_p_t;


/*   BROADCAST TYPE = BD39  */

typedef struct directed_trade_change
{
   broadcast_type_t broadcast_type;
   cl_trade_change_api_t cl_trade_change_api;
} directed_trade_change_t;


/*   TRANSACTION TYPE = KB1  */

typedef struct directed_trade_report
{
   broadcast_type_t broadcast_type;
   uint8_t broadcast_reason_c;
   char filler_3_s [3];
   uint16_t items_n;
   uint16_t size_n;
} directed_trade_report_t;


/*   TRANSACTION TYPE = BI81, UA14  */
/*   NAMED STRUCT = 35004  */

typedef struct document_url
{
   uint8_t items_c;
   char url_link_s [255];
} document_url_t;


/*   BROADCAST TYPE = BO10  */

typedef struct equil_price_update
{
   broadcast_type_t broadcast_type;
   uint16_t items_n;
   char filler_2_s [2];
   equil_price_update_item_t item [27];
} equil_price_update_t;


/*   BROADCAST TYPE = BL2156  */

typedef struct etpr_delta_limit_change
{
   broadcast_type_t broadcast_type;
   uint16_t items_n;
   char filler_2_s [2];
   etpr_delta_limit_change_item_t item [40];
} etpr_delta_limit_change_t;


/*   BROADCAST TYPE = BL2155  */

typedef struct etpr_limit_change
{
   broadcast_type_t broadcast_type;
   uint16_t items_n;
   char filler_2_s [2];
   etpr_limit_change_item_t item [40];
} etpr_limit_change_t;


/*   BROADCAST TYPE = BU78  */

typedef struct exception_days_update_bu78
{
   broadcast_type_t broadcast_type;
   uint16_t chg_type_n;
   char filler_2_s [2];
   da78_t da78;
} exception_days_update_bu78_t;


/*   TRANSACTION TYPE = BO25, BO5, BO55, MO1, MO3, MO385, MO387  */
/*   NAMED STRUCT = 50004  */

typedef struct exchange_info
{
   char exchange_info_s [32];
} exchange_info_t;


/*   TRANSACTION TYPE = CC13  */

typedef struct exercise_req
{
   transaction_type_t transaction_type;
   series_t series;
   account_t account;
   int64_t quantity_i;
   int32_t trade_number_i;
} exercise_req_t;


/*   TRANSACTION TYPE = BD70, TA70  */
/*   NAMED STRUCT = 34402  */

typedef struct extended_trade_ticker
{
   uint16_t trade_condition_n;
   uint16_t deal_info_n;
} extended_trade_ticker_t;


/*   TRANSACTION TYPE = BD70, TA70  */
/*   NAMED STRUCT = 34404  */

typedef struct fixed_income_trade_ticker
{
   int32_t corresponding_yield_price_i;
} fixed_income_trade_ticker_t;


/*   TRANSACTION TYPE = BO25, BO5, MO1, MO3, MO385, MO387  */
/*   NAMED STRUCT = 34801  */

typedef struct free_text
{
   char customer_info_s [15];
   char filler_1_s;
} free_text_t;


/*   TRANSACTION TYPE = CD35  */

typedef struct give_up_request
{
   transaction_type_t transaction_type;
   series_t series;
   account_t account;
   int32_t trade_number_i;
   int64_t trade_quantity_i;
   int32_t commission_i;
   char give_up_text_s [30];
   char filler_2_s [2];
} give_up_request_t;


/*   TRANSACTION TYPE = FA1, FA2, FB1  */
/*   NAMED STRUCT = 18001  */

typedef struct guarantee
{
   collateral_base_t collateral_base;
   uint8_t guarantee_type_c;
   char filler_3_s [3];
} guarantee_t;


/*   BROADCAST TYPE = BU47  */

typedef struct haircut_update_bu47
{
   broadcast_type_t broadcast_type;
   uint16_t chg_type_n;
   char filler_2_s [2];
   da47_t da47;
} haircut_update_bu47_t;


/*   TRANSACTION TYPE = BD70, BD71, TA70, TA71  */
/*   NAMED STRUCT = 34405  */

typedef struct half_trade_ticker
{
   trading_code_t trading_code;
   int64_t trade_quantity_i;
   uint32_t block_n;
   uint8_t bid_or_ask_c;
   uint8_t deal_source_c;
   char filler_2_s [2];
} half_trade_ticker_t;


/*   TRANSACTION TYPE = BO25, BO5, MO99  */
/*   NAMED STRUCT = 34010  */

typedef struct hv_alter_trans
{
   transaction_type_t transaction_type;
   series_t series;
   quad_word order_number_u;
   order_var_t order_var;
   give_up_member_t give_up_member;
   char exchange_info_s [32];
   int64_t total_volume_i;
   uint8_t delta_quantity_c;
   char filler_3_s [3];
   int64_t balance_quantity_i;
} hv_alter_trans_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34110  */

typedef struct hv_alter_trans_p
{
   transaction_type_t transaction_type;
   series_t series;
   trading_code_t trading_code;
   quad_word order_number_u;
   order_var_t order_var;
   give_up_member_t give_up_member;
   char exchange_info_s [32];
   int64_t total_volume_i;
   uint8_t delta_quantity_c;
   char filler_3_s [3];
   int64_t balance_quantity_i;
} hv_alter_trans_p_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34005  */

typedef struct hv_order_trans
{
   transaction_type_t transaction_type;
   series_t series;
   order_var_t order_var;
   give_up_member_t give_up_member;
   char exchange_info_s [32];
   int64_t total_volume_i;
} hv_order_trans_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34105  */

typedef struct hv_order_trans_p
{
   transaction_type_t transaction_type;
   series_t series;
   trading_code_t trading_code;
   order_var_t order_var;
   give_up_member_t give_up_member;
   char exchange_info_s [32];
   int64_t total_volume_i;
} hv_order_trans_p_t;


/*   TRANSACTION TYPE = BO25, BO5, MO37  */
/*   NAMED STRUCT = 34001  */

typedef struct hv_price_2_trans
{
   transaction_type_t transaction_type;
   series_t series;
   give_up_member_t give_up_member;
   quad_word order_number_bid_u;
   quad_word order_number_ask_u;
   int32_t bid_premium_i;
   int32_t ask_premium_i;
   int64_t bid_quantity_i;
   int64_t ask_quantity_i;
   int64_t bid_total_volume_i;
   int64_t ask_total_volume_i;
   uint32_t block_n;
   uint16_t time_validity_n;
   char ex_client_s [16];
   uint8_t order_type_c;
   char customer_info_s [15];
   char exchange_info_s [32];
   uint16_t stp_key_i;
} hv_price_2_trans_t;


/*   TRANSACTION TYPE = BO25, BO5, MO421  */
/*   NAMED STRUCT = 34101  */

typedef struct hv_price_2_trans_p
{
   transaction_type_t transaction_type;
   series_t series;
   trading_code_t trading_code;
   give_up_member_t give_up_member;
   quad_word order_number_bid_u;
   quad_word order_number_ask_u;
   int32_t bid_premium_i;
   int32_t ask_premium_i;
   int64_t bid_quantity_i;
   int64_t ask_quantity_i;
   int64_t bid_total_volume_i;
   int64_t ask_total_volume_i;
   uint32_t block_n;
   uint16_t time_validity_n;
   char ex_client_s [16];
   uint8_t order_type_c;
   char customer_info_s [15];
   char exchange_info_s [32];
   uint16_t stp_key_i;
} hv_price_2_trans_p_t;


/*   TRANSACTION TYPE = BO25, BO5, MA476, MA92  */
/*   NAMED STRUCT = 34818  */

typedef struct inactive_order
{
   uint8_t inactive_c;
   char filler_3_s [3];
} inactive_order_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34025  */

typedef struct indicative_quote
{
   series_t series;
   int64_t buy_quantity_u;
   int64_t sell_quantity_u;
   int32_t buy_price_i;
   int32_t sell_price_i;
   uint8_t bid_quote_action;
   uint8_t ask_quote_action;
   char filler_2_s [2];
} indicative_quote_t;


/*   BROADCAST TYPE = BI9  */

typedef struct info_heartbeat
{
   broadcast_type_t broadcast_type;
   uint8_t heartbeat_interval_c;
   uint8_t instance_c;
   uint8_t tot_instances_c;
   char description_s [40];
   char filler_1_s;
} info_heartbeat_t;


/*   TRANSACTION TYPE = BI84  */

typedef struct info_ready
{
   broadcast_type_t broadcast_type;
   int32_t info_type_i;
   series_t series;
   char business_date_s [8];
   char sent_date_s [8];
   char sent_time_s [6];
   char clearing_date_s [8];
   uint16_t seq_num_srm_n;
} info_ready_t;


/*   BROADCAST TYPE = BI41  */

typedef struct instrument_status_info
{
   broadcast_type_t broadcast_type;
   uint16_t items_n;
   char filler_2_s [2];
   instrument_status_info_item_t item [9];
} instrument_status_info_t;


/*   BROADCAST TYPE = BU10, BU20  */

typedef struct inst_class_update_bu10_bu20
{
   broadcast_type_t broadcast_type;
   uint16_t chg_type_n;
   char filler_2_s [2];
   da10_da20_t da10_da20;
} inst_class_update_bu10_bu20_t;


/*   TRANSACTION TYPE = KA1, KB1, KB14, KC1  */
/*   NAMED STRUCT = 38008  */

typedef struct irs_counterparty_pay
{
   irs_leg_t irs_leg;
} irs_counterparty_pay_t;


/*   TRANSACTION TYPE = KA1, KB1, KB14, KC1  */
/*   NAMED STRUCT = 38007  */

typedef struct irs_member_pay
{
   irs_leg_t irs_leg;
} irs_member_pay_t;


/*   TRANSACTION TYPE = BD2, BO16, BO17, BU120, BU121, BU122, BU123, BU124, BU125, BU126, BU134, BU136, BU90, CA10, CA11, CA117, CA128, CA129, CA132, CC91, CC92, DA120, DA121, DA122, DA123, DA124, DA125, DA126, DA130, DA131, DA134, DA136, DA90, DC90, FA1, FA14, FA15, FA16, FA17, FA19, FA2, FA20, FA21, FA22, FA24, FA29, FA40, FQ40, IA21, IA22, JA1, JA10, JA11, JA21, JA277, JA31, JA54, JA55, JA7, JA71, JA9, JC9, JQ71, KA1, KC1, MA476, MA92, TA70, TA71, UA14  */

typedef struct item_hdr
{
   uint16_t items_n;
   uint16_t size_n;
} item_hdr_t;


/*   BROADCAST TYPE = BL51  */

typedef struct limit_change
{
   broadcast_type_t broadcast_type;
   uint16_t items_n;
   char filler_2_s [2];
   limit_change_item_t item [50];
} limit_change_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34024  */

typedef struct long_stop_order_trans
{
   transaction_type_t transaction_type;
   series_t series;
   order_var_t order_var;
   stop_series_t stop_series;
   int32_t limit_premium_i;
   give_up_member_t give_up_member;
   char exchange_info_s [32];
   int64_t total_volume_i;
} long_stop_order_trans_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34124  */

typedef struct long_stop_order_trans_p
{
   transaction_type_t transaction_type;
   series_t series;
   trading_code_t trading_code;
   order_var_t order_var;
   stop_series_t stop_series;
   int32_t limit_premium_i;
   give_up_member_t give_up_member;
   char exchange_info_s [32];
   int64_t total_volume_i;
} long_stop_order_trans_p_t;


/*   TRANSACTION TYPE = JC9  */
/*   NAMED STRUCT = 21122  */

typedef struct marginable_spread_item
{
   account_t account;
   series_t series;
   int64_t rpt_intra_held_q;
   int64_t rpt_intra_written_q;
   int64_t rpt_inter_held_q;
   int64_t rpt_inter_written_q;
} marginable_spread_item_t;


/*   TRANSACTION TYPE = FA19  */
/*   NAMED STRUCT = 18051  */

typedef struct margin_collateral_evaluation
{
   margin_account_t margin_account;
   account_t cash_optimization_account;
   currency_t currency;
   currency_t base_currency;
   int64_t settlement_requirement_q;
   int64_t collateral_cash_q;
   int64_t adjusted_collateral_cash_q;
   int64_t collateral_cash_after_settlement_q;
   int64_t collateral_noncash_q;
   int64_t credit_debit_coll_acc_margin_q;
   int64_t credit_debit_coll_acc_settlement_q;
   int64_t total_credit_debit_coll_acc_q;
   int64_t ext_credit_debit_margin_q;
   int64_t ext_credit_debit_settlement_q;
   int64_t total_ext_credit_debit_q;
   int64_t margin_total_q;
   int64_t total_collateral_value_q;
   int64_t total_surplus_deficit_q;
   int64_t total_surplus_deficit_base_cur_q;
   int64_t total_surplus_deficit_base_cur_after_fx_haircut_q;
   int64_t ex_rate_q;
   int64_t cash_collateral_limit_q;
   int64_t direct_credit_limit_q;
   char instr_ref_s [16];
   int32_t fx_percentage_after_haircut_i;
   uint16_t dec_in_rate_n;
   uint8_t dd_in_base_c;
   char filler_1_s;
} margin_collateral_evaluation_t;


/*   TRANSACTION TYPE = FA19  */
/*   NAMED STRUCT = 18065  */

typedef struct margin_collateral_evaluation_base_sgx
{
   margin_account_t margin_account;
   currency_t currency;
   currency_t base_currency;
   int64_t settlement_requirement_q;
   int64_t collateral_cash_q;
   int64_t acc_bal_residual_q;
   int64_t collateral_fixed_income_q;
   int64_t collateral_equity_q;
   int64_t collateral_guarantee_q;
   int64_t collateral_noncash_q;
   int64_t total_collateral_value_q;
   int64_t margin_maintenance_q;
   int64_t margin_extraordinary_q;
   int64_t total_margin_req_q;
   int64_t external_margin_req_q;
   int64_t margin_total_q;
   int64_t ex_rate_q;
   int64_t acc_bal_residual_base_cur_q;
   int64_t collateral_cash_base_cur_q;
   int64_t collateral_noncash_base_cur_q;
   int64_t external_margin_req_base_cur_q;
   int64_t margin_maintenance_base_cur_q;
   int64_t margin_extraordinary_base_cur_q;
   int64_t margin_total_base_cur_q;
   int64_t ext_credit_debit_margin_q;
   int64_t ext_credit_debit_settlement_q;
   int64_t total_ext_credit_debit_q;
   char settlement_date_s [8];
   uint16_t dec_in_rate_n;
   char filler_2_s [2];
} margin_collateral_evaluation_base_sgx_t;


/*   TRANSACTION TYPE = FA19  */
/*   NAMED STRUCT = 18059  */

typedef struct margin_collateral_evaluation_cash_optimization
{
   account_t cash_optimization_account;
   currency_t currency;
   int64_t total_ext_credit_debit_q;
   char instr_ref_s [16];
} margin_collateral_evaluation_cash_optimization_t;


/*   TRANSACTION TYPE = FA19  */
/*   NAMED STRUCT = 18067  */

typedef struct margin_collateral_evaluation_collrank_sgx
{
   int64_t usd_equivalent_q;
   int64_t collateral_fixed_income_base_cur_q;
   int64_t collateral_equity_base_cur_q;
   int64_t collateral_guarantee_base_cur_q;
   int64_t total_collateral_value_base_cur_q;
   int64_t total_margin_req_base_cur_q;
   int64_t rank1_surpl_def_base_cur_after_fx_haircut_q;
   int64_t rank2_surpl_def_base_cur_after_fx_haircut_q;
   int64_t rank3_surpl_def_base_cur_after_fx_haircut_q;
   int64_t rank4_surpl_def_base_cur_after_fx_haircut_q;
   int64_t rank5_surpl_def_base_cur_after_fx_haircut_q;
   int32_t rank1_fx_percentage_after_haircut_i;
   int32_t rank2_fx_percentage_after_haircut_i;
   int32_t rank3_fx_percentage_after_haircut_i;
   int32_t rank4_fx_percentage_after_haircut_i;
   int32_t rank5_fx_percentage_after_haircut_i;
   int64_t equity_surplus_deficit_base_cur_q;
   int64_t equity_sd_base_cur_after_fx_haircut_q;
   int32_t rank3_surp_fx_percentage_after_haircut_i;
   int64_t allocated_equity_deficit_base_cur_q;
} margin_collateral_evaluation_collrank_sgx_t;


/*   TRANSACTION TYPE = FA19  */
/*   NAMED STRUCT = 18068  */

typedef struct margin_collateral_evaluation_df_sgx
{
   int64_t cash_df_requirement_q;
   int64_t cash_surplus_deficit_q;
   int64_t noncash_surplus_deficit_q;
   int64_t cash_df_requirement_base_cur_q;
   int64_t cash_surplus_deficit_base_cur_q;
   int64_t noncash_surplus_deficit_base_cur_q;
   int32_t fx_percentage_after_haircut_i;
} margin_collateral_evaluation_df_sgx_t;


/*   TRANSACTION TYPE = FA19  */
/*   NAMED STRUCT = 18052  */

typedef struct margin_collateral_evaluation_grand_total
{
   margin_account_t margin_account;
   currency_t base_currency;
   int64_t grand_total_surplus_deficit_base_cur_q;
   int64_t grand_total_surplus_deficit_base_cur_after_fx_haircut_q;
} margin_collateral_evaluation_grand_total_t;


/*   TRANSACTION TYPE = FA19  */
/*   NAMED STRUCT = 18066  */

typedef struct margin_collateral_evaluation_grand_total_sgx
{
   margin_account_t margin_account;
   currency_t base_currency;
   int64_t sum_rank1_surpl_def_base_cur_after_fx_haircut_q;
   int64_t sum_rank2_surpl_def_base_cur_after_fx_haircut_q;
   int64_t sum_rank3_surpl_def_base_cur_after_fx_haircut_q;
   int64_t sum_rank4_surpl_def_base_cur_after_fx_haircut_q;
   int64_t sum_rank5_surpl_def_base_cur_after_fx_haircut_q;
   int64_t margin_total_base_cur_q;
   int64_t sum_noncash_surplus_deficit_base_cur_q;
   int64_t sum_cash_surplus_deficit_base_cur_q;
   int64_t grand_total_surplus_deficit_base_cur_after_fx_haircut_q;
} margin_collateral_evaluation_grand_total_sgx_t;


/*   TRANSACTION TYPE = JA54  */
/*   NAMED STRUCT = 21131  */

typedef struct margin_result_additional_margin
{
   int64_t additional_margin_q;
} margin_result_additional_margin_t;


/*   TRANSACTION TYPE = JA54, JA55  */
/*   NAMED STRUCT = 21064  */

typedef struct margin_result_base_api
{
   int64_t total_margin_req_q;
   int64_t initial_margin_req_q;
   int64_t variation_margin_req_q;
   int64_t contingent_variation_margin_req_q;
   int64_t info_naked_risk_margin_q;
} margin_result_base_api_t;


/*   TRANSACTION TYPE = JA54, JA55  */
/*   NAMED STRUCT = 21062  */

typedef struct margin_result_components
{
   int64_t risk_margin_open_q;
   int64_t risk_margin_deliv_q;
   int64_t spot_val_margin_q;
   int64_t for_val_margin_q;
   int64_t fut_val_margin_q;
   int64_t opt_val_margin_q;
   int64_t deliv_val_margin_q;
   int64_t payment_margin_future_date_q;
   int64_t long_opt_min_val_q;
   int64_t today_opt_premium_q;
   char risk_currency_s [3];
   char instr_currency_s [3];
   uint8_t instrument_or_risk_currency_c;
   char filler_1_s;
} margin_result_components_t;


/*   TRANSACTION TYPE = JA54, JA55  */
/*   NAMED STRUCT = 21066  */

typedef struct margin_result_components_cfm
{
   int64_t info_market_value_theo_q;
   int64_t market_value_margin_settled_q;
} margin_result_components_cfm_t;


/*   TRANSACTION TYPE = JA54, JA55  */
/*   NAMED STRUCT = 21065  */

typedef struct margin_result_components_pdh
{
   int64_t financial_margin_q;
   int64_t info_inter_comm_spread_credit_q;
} margin_result_components_pdh_t;


/*   TRANSACTION TYPE = JA54  */
/*   NAMED STRUCT = 21132  */

typedef struct margin_result_otcf_margin
{
   int64_t otcf_margin_q;
   int64_t otcf_additional_margin_q;
   int64_t pai_q;
   int64_t otcf_settlement_variation_q;
} margin_result_otcf_margin_t;


/*   TRANSACTION TYPE = JA54, JA55  */
/*   NAMED STRUCT = 21063  */

typedef struct margin_result_overdue
{
   int64_t delivery_margin_valuation_date_q;
   int64_t delivery_margin_overdue_q;
   int64_t payment_margin_valuation_date_q;
   int64_t payment_margin_overdue_q;
} margin_result_overdue_t;


/*   TRANSACTION TYPE = JA7  */
/*   NAMED STRUCT = 21040  */

typedef struct margin_result_pos_unit_api
{
   account_t account;
   series_t series;
   int64_t pos_unit_id_q;
   int64_t margin_req_u;
   int64_t market_value_q;
   int64_t nbr_held_q;
   int64_t nbr_written_q;
   int64_t naked_margin_q;
   int64_t today_option_premium_q;
   int64_t risk_margin_without_scaling_q;
   int64_t offset_reduction_adj_q;
   char currency_s [3];
   uint8_t gross_or_net_c;
   char margin_class_s [3];
   uint8_t marg_meth_inst_c;
   uint8_t marg_item_type_c;
   uint8_t account_calculation_type_c;
   char filler_2_s [2];
} margin_result_pos_unit_api_t;


/*   TRANSACTION TYPE = JA7  */
/*   NAMED STRUCT = 21058  */

typedef struct margin_result_pos_unit_cfm
{
   int64_t market_value_theo_q;
   int64_t price_spread_margin_q;
   int64_t sensitivity_forecast_primary_q;
   int64_t sensitivity_discount_primary_q;
   int64_t market_value_margin_settled_q;
   int64_t sensitivity_forecast_secondary_q;
   int64_t sensitivity_discount_secondary_q;
} margin_result_pos_unit_cfm_t;


/*   TRANSACTION TYPE = JA7  */
/*   NAMED STRUCT = 21060  */

typedef struct margin_result_pos_unit_delivery
{
   char closing_date_s [8];
   char settlement_date_s [8];
} margin_result_pos_unit_delivery_t;


/*   TRANSACTION TYPE = JA7  */
/*   NAMED STRUCT = 21059  */

typedef struct margin_result_pos_unit_forward
{
   int64_t acc_bought_for_q;
   int64_t acc_sold_for_q;
} margin_result_pos_unit_forward_t;


/*   TRANSACTION TYPE = JA7  */
/*   NAMED STRUCT = 21057  */

typedef struct margin_result_pos_unit_pdh
{
   int64_t cash_margin_q;
   int64_t orig_market_value_q;
   int64_t unconv_market_value_q;
   int64_t financial_margin_q;
   int64_t inter_comm_spread_credit_q;
   int64_t quantity_rnp_q;
   int64_t rest_long_pos_bef_inter_comm_q;
   int64_t rest_short_pos_bef_inter_comm_q;
   char cash_currency_s [3];
   char filler_1_s;
   int64_t contract_spread_credit_q;
   int64_t time_spread_credit_q;
} margin_result_pos_unit_pdh_t;


/*   TRANSACTION TYPE = JA7  */
/*   NAMED STRUCT = 21100  */

typedef struct margin_result_pos_unit_settlement
{
   char settlement_date_s [8];
} margin_result_pos_unit_settlement_t;


/*   TRANSACTION TYPE = JA1, JB1, JB2  */
/*   NAMED STRUCT = 21000  */

typedef struct marg_calc_runs
{
   char clh_id_s [12];
   char valuation_date_s [8];
   char start_date_s [8];
   char start_time_s [6];
   uint8_t incl_t_plus_one_prices_c;
   uint8_t incl_t_plus_one_positions_c;
   int32_t sequence_number_n;
   uint8_t run_type_c;
   char filler_3_s [3];
} marg_calc_runs_t;


/*   TRANSACTION TYPE = BD2, IA21, IA22  */
/*   NAMED STRUCT = 33034  */

typedef struct market_info_base
{
   int32_t opening_price_i;
   int32_t high_price_i;
   int32_t low_price_i;
   int32_t last_price_i;
   int64_t volume_u;
   int64_t turnover_u;
   uint32_t number_of_deals_u;
   char hhmmss_s [6];
   char trend_indicator_c;
   uint8_t deal_source_c;
} market_info_base_t;


/*   TRANSACTION TYPE = BD2, IA21, IA22  */
/*   NAMED STRUCT = 33040  */

typedef struct market_info_index
{
   int32_t opening_price_i;
   int32_t high_price_i;
   int32_t low_price_i;
   int32_t last_price_i;
   int32_t change_previous_i;
   int32_t change_yesterday_i;
   int32_t points_of_movement_i;
   char date_time_of_dist_s [14];
   char date_time_of_comp_s [14];
} market_info_index_t;


/*   TRANSACTION TYPE = BD2, IA21, IA22  */
/*   NAMED STRUCT = 33035  */

typedef struct market_info_net
{
   int32_t net_change_i;
} market_info_net_t;


/*   TRANSACTION TYPE = BD2  */
/*   NAMED STRUCT = 33043  */

typedef struct market_info_reason
{
   uint8_t edited_price_info_reason_c;
   char filler_3_s [3];
} market_info_reason_t;


/*   TRANSACTION TYPE = BD2  */
/*   NAMED STRUCT = 33038  */

typedef struct market_info_series
{
   series_t series;
   int32_t reserved_i;
   uint8_t all_or_none_c;
   char filler_3_s [3];
} market_info_series_t;


/*   TRANSACTION TYPE = BD2, IA21, IA22  */
/*   NAMED STRUCT = 33046  */

typedef struct market_info_sgx
{
   int64_t turnover_value_q;
   int64_t trade_reported_volume_u;
   int64_t trade_reported_volume_t_session_u;
   uint32_t combo_quantity_u;
   int32_t previous_last_price_i;
   char previous_last_price_updated_date_s [8];
   char previous_last_price_updated_time_s [6];
   char filler_2_s [2];
} market_info_sgx_t;


/*   TRANSACTION TYPE = BD2, IA21, IA22  */
/*   NAMED STRUCT = 33036  */

typedef struct market_info_trd
{
   int32_t last_trade_report_price_i;
   int64_t last_trade_report_qty_u;
} market_info_trd_t;


/*   BROADCAST TYPE = BO38  */

typedef struct market_maker_protection_info
{
   broadcast_type_t broadcast_type;
   trading_code_t trading_code;
   series_t series;
   int64_t calc_quantity_protection_q;
   int64_t calc_delta_protection_q;
} market_maker_protection_info_t;


/*   TRANSACTION TYPE = MO96  */

typedef struct mass_quote_trans
{
   transaction_type_t transaction_type;
   series_t series;
   stp_key_t stp_key;
   uint16_t items_n;
   char filler_2_s [2];
   mass_quote_trans_item_t item [36];
} mass_quote_trans_t;


/*   BROADCAST TYPE = BO96  */

typedef struct mass_quote_update
{
   broadcast_type_t broadcast_type;
   trading_code_t trading_code;
   time_spec_t execution_timestamp;
   quad_word order_number_u;
   uint32_t sequence_number_u;
   uint16_t stp_key_i;
   uint16_t items_n;
   mass_quote_update_item_t item [36];
} mass_quote_update_t;


/*   TRANSACTION TYPE = FA1, FA2, FB1  */
/*   NAMED STRUCT = 18002  */

typedef struct member_deposit
{
   collateral_base_t collateral_base;
   uint8_t member_deposit_type_c;
   char filler_3_s [3];
   char fund_name_s [32];
} member_deposit_t;


/*   TRANSACTION TYPE = BI81, UA14  */
/*   NAMED STRUCT = 35001  */

typedef struct message_core_info
{
   uint32_t sequence_number_u;
   uint8_t message_information_type_c;
   char message_source_s [80];
   char yyyymmdd_s [8];
   char hhmmss_s [6];
   uint8_t message_priority_c;
   char message_header_s [80];
   uint8_t update_status_note_c;
   char filler_3_s [3];
} message_core_info_t;


/*   TRANSACTION TYPE = BI81, UA14  */
/*   NAMED STRUCT = 35002  */

typedef struct message_information
{
   uint16_t items_n;
   char filler_2_s [2];
   message_information_item_t item [10];
} message_information_t;


/*   BROADCAST TYPE = BU87  */

typedef struct mm_protection_update
{
   broadcast_type_t broadcast_type;
   uint16_t chg_type_n;
   char filler_2_s [2];
   da87_t da87;
} mm_protection_update_t;


/*   TRANSACTION TYPE = CC92  */

typedef struct modify_aat_connection_hdr
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t items_n;
   uint8_t connect_type_c;
   char filler_1_s;
   participant_t participant;
   char acc_access_type_s [64];
   int32_t version_i;
} modify_aat_connection_hdr_t;


/*   TRANSACTION TYPE = CC22  */

typedef struct modify_account
{
   transaction_type_t transaction_type;
   series_t series;
   auth_section_t auth_section;
   account_t account;
   account_data_external_t account_data_external;
} modify_account_t;


/*   TRANSACTION TYPE = CC89  */

typedef struct modify_acc_access_type
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t items_n;
   char filler_2_s [2];
   participant_t participant;
   char acc_access_type_s [64];
   char desc_long_s [128];
   int32_t allow_all_account_i;
   int32_t version_i;
   modify_acc_access_type_item_t item [2600];
} modify_acc_access_type_t;


/*   TRANSACTION TYPE = CC41  */

typedef struct modify_commission
{
   transaction_type_t transaction_type;
   series_t series;
   party_t party;
   uint8_t send_receive_c;
   char filler_1_s;
   uint16_t items_n;
   modify_commission_item_t item [760];
} modify_commission_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34918  */

typedef struct mp_trade_price
{
   series_t series;
   quad_word order_number_u;
   uint8_t bid_or_ask_c;
   uint8_t deal_source_c;
   uint16_t trade_condition_n;
   int32_t deal_price_i;
   int64_t deal_quantity_i;
   uint8_t ext_t_state_c;
   uint8_t opposing_deal_source_c;
   uint16_t exch_order_type_n;
   quad_word opposing_order_number_u;
} mp_trade_price_t;


/*   TRANSACTION TYPE = JA54, JA55  */
/*   NAMED STRUCT = 50007  */

typedef struct mra_account_vim
{
   account_t account;
} mra_account_vim_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34906  */

typedef struct multi_order_response
{
   int32_t transaction_status_i;
   int32_t trans_ack_i;
   uint8_t item_number_c;
   char filler_3_s [3];
} multi_order_response_t;


/*   BROADCAST TYPE = BU18  */

typedef struct non_trading_days_update_bu18
{
   broadcast_type_t broadcast_type;
   uint16_t chg_type_n;
   char filler_2_s [2];
   da18_t da18;
} non_trading_days_update_bu18_t;


/*   BROADCAST TYPE = BU50  */

typedef struct non_trad_settl_days_update_bu50
{
   broadcast_type_t broadcast_type;
   uint16_t chg_type_n;
   char filler_2_s [2];
   da50_t da50;
} non_trad_settl_days_update_bu50_t;


/*   TRANSACTION TYPE = BU134, DA134  */
/*   NAMED STRUCT = 37901  */

typedef struct ns_account_type_basic
{
   char acc_type_s [12];
   char description_s [40];
   uint8_t open_close_c;
   uint8_t transitory_c;
   uint8_t market_maker_c;
   uint8_t own_inventory_c;
   uint8_t exclusive_opening_sell_c;
   uint8_t positions_allowed_c;
   uint8_t trades_allowed_c;
   char atr_id_s [12];
   char origin_c;
   uint8_t allowed_collateral_c;
   char acct_type_c;
   uint8_t custodian_c;
   char filler_1_s;
} ns_account_type_basic_t;


/*   TRANSACTION TYPE = BU122, BU123, DA122, DA123  */
/*   NAMED STRUCT = 37103  */

typedef struct ns_block_size
{
   int64_t maximum_size_u;
   uint32_t minimum_size_n;
   uint32_t block_n;
   uint8_t lot_type_c;
   char filler_3_s [3];
} ns_block_size_t;


/*   TRANSACTION TYPE = BU122, BU123, DA122, DA123  */
/*   NAMED STRUCT = 37104  */

typedef struct ns_calc_rule
{
   uint32_t accr_intr_round_u;
   uint32_t clean_pr_round_u;
   uint16_t yield_conv_n;
   uint16_t ex_coupon_n;
   uint8_t accr_intr_ud_c;
   uint8_t clean_pr_ud_c;
   uint8_t day_count_conv_c;
   uint8_t eom_count_conv_c;
   uint8_t set_start_consid_c;
   uint8_t set_end_consid_c;
   uint8_t calculation_conv_c;
   uint8_t ex_coupon_calc_type_c;
} ns_calc_rule_t;


/*   TRANSACTION TYPE = BU126, BU136, DA126, DA136  */
/*   NAMED STRUCT = 37308  */

typedef struct ns_combo_series_leg
{
   series_t series;
   uint16_t ratio_n;
   char op_if_buy_c;
   char op_if_sell_c;
} ns_combo_series_leg_t;


/*   TRANSACTION TYPE = BU120, BU121, DA120, DA121  */
/*   NAMED STRUCT = 37203  */

typedef struct ns_coupon_dates
{
   char date_coupdiv_s [8];
   char date_booksclose_s [8];
   uint32_t dividend_i;
} ns_coupon_dates_t;


/*   TRANSACTION TYPE = BU120, BU121, BU122, BU123, BU124, BU125, DA120, DA121, DA122, DA123, DA124, DA125  */
/*   NAMED STRUCT = 37001  */

typedef struct ns_delta_header
{
   int64_t download_ref_number_q;
   time_spec_t full_answer_timestamp;
   uint8_t full_answer_c;
   char filler_3_s [3];
} ns_delta_header_t;


/*   TRANSACTION TYPE = BU120, BU121, DA120, DA121  */
/*   NAMED STRUCT = 37202  */

typedef struct ns_fixed_income
{
   int64_t nominal_value_q;
   uint32_t coupon_interest_i;
   uint16_t dec_in_nominal_n;
   uint16_t coupon_settlement_days_n;
   uint16_t coupon_frequency_n;
   uint16_t rate_determ_days_n;
   char date_release_s [8];
   char date_termination_s [8];
   char date_dated_s [8];
   char date_proceed_s [8];
   uint8_t fixed_income_type_c;
   uint8_t day_calc_rule_c;
   char filler_2_s [2];
} ns_fixed_income_t;


/*   TRANSACTION TYPE = BU122, BU123, DA122, DA123  */
/*   NAMED STRUCT = 37101  */

typedef struct ns_inst_class_basic
{
   series_t series;
   upper_level_series_t upper_level_series;
   int32_t price_quot_factor_i;
   int32_t contract_size_i;
   int32_t redemption_value_i;
   int32_t undisclosed_min_ord_val_i;
   int32_t opt_min_ord_val_i;
   int32_t opt_min_trade_val_i;
   uint16_t derivate_level_n;
   uint16_t dec_in_strike_price_n;
   uint16_t dec_in_contr_size_n;
   uint16_t rnt_id_n;
   uint16_t virt_commodity_n;
   uint16_t settlement_days_n;
   uint8_t settl_day_unit_c;
   char inc_id_s [14];
   char name_s [32];
   char trc_id_s [10];
   char base_cur_s [3];
   uint8_t traded_c;
   uint8_t price_unit_premium_c;
   uint8_t price_unit_strike_c;
   uint8_t trd_cur_unit_c;
   uint8_t db_operation_c;
   char filler_3_s [3];
} ns_inst_class_basic_t;


/*   TRANSACTION TYPE = BU123, DA123  */
/*   NAMED STRUCT = 37114  */

typedef struct ns_inst_class_cms
{
   char valuation_group_id_s [12];
   char haircut_id_s [12];
   int32_t vag_limit_i;
   uint8_t collateral_type_c;
   uint8_t eligible_as_margin_coll_c;
   uint8_t eligible_as_def_fund_coll_c;
   char filler_1_s;
} ns_inst_class_cms_t;


/*   TRANSACTION TYPE = BU123, DA123  */
/*   NAMED STRUCT = 37139  */

typedef struct ns_inst_class_ext14
{
   uint8_t tar_instrument_indicator_c;
   char filler_1_s;
   char reference_inc_id_s [14];
   int16_t max_length_expiration_i;
   int16_t trade_days_ltd_exp_i;
   int16_t trade_days_sett_exp_i;
   int16_t trade_days_delv_start_exp_i;
   int16_t trade_days_delv_end_exp_i;
   char filler_2_s [2];
} ns_inst_class_ext14_t;


/*   TRANSACTION TYPE = BU122, DA122  */
/*   NAMED STRUCT = 37127  */

typedef struct ns_inst_class_oat
{
   uint8_t limit_order_allwd_c;
   uint8_t market_orders_allowed_c;
   uint8_t fill_or_kill_allowed_c;
   uint8_t fill_and_kill_allowed_c;
   uint8_t fill_and_store_c;
   uint8_t all_or_none_c;
   uint8_t imb_orders_allwd_c;
   uint8_t mtl_orders_rlot_allwd_c;
   uint8_t allow_hidd_aggr_c;
   uint8_t best_limit_c;
   uint8_t market_bid_c;
   uint8_t price_stabilization_c;
   uint8_t short_sell_c;
   uint8_t short_sell_validation_c;
   uint8_t allow_cp_mar_c;
   uint8_t allow_cp_lim_c;
   uint8_t allow_undisclosed_qty_c;
   uint8_t sso_orders_allowed_c;
   uint8_t stop_orders_allowed_c;
   uint8_t good_till_session_c;
   uint8_t priority_ranking_c;
   char filler_3_s [3];
} ns_inst_class_oat_t;


/*   TRANSACTION TYPE = BU122, BU123, DA122, DA123  */
/*   NAMED STRUCT = 37105  */

typedef struct ns_inst_class_secur
{
   int32_t exerc_limit_i;
   uint16_t dec_in_deliv_n;
   uint16_t cleared_dec_in_qty_n;
   uint16_t dec_in_fixing_n;
   uint8_t exerc_limit_unit_c;
   char settl_cur_id_s [32];
   char csd_id_s [12];
   uint8_t fixing_req_c;
} ns_inst_class_secur_t;


/*   TRANSACTION TYPE = BU124, BU125, BU126, BU136, DA124, DA125, DA126, DA136  */
/*   NAMED STRUCT = 37301  */

typedef struct ns_inst_series_basic
{
   series_t series;
   uint16_t step_size_multiple_n;
   char ins_id_s [32];
   char long_ins_id_s [32];
   char date_last_trading_s [8];
   char time_last_trading_s [6];
   char date_first_trading_s [8];
   char time_first_trading_s [6];
   uint8_t series_status_c;
   uint8_t suspended_c;
   uint8_t traded_in_click_c;
   uint8_t db_operation_c;
   uint8_t trade_reporting_only_c;
   uint8_t traded_c;
} ns_inst_series_basic_t;


/*   TRANSACTION TYPE = BU124, BU125, DA124, DA125  */
/*   NAMED STRUCT = 37302  */

typedef struct ns_inst_series_basic_single
{
   upper_level_series_t upper_level_series;
   int32_t contract_size_i;
   int32_t price_quot_factor_i;
   uint16_t state_number_n;
   uint16_t ex_coupon_n;
   char isin_code_s [12];
   char settlement_date_s [8];
   char first_settlement_date_s [8];
   char date_notation_s [8];
   uint8_t deliverable_c;
   char effective_exp_date_s [8];
   uint8_t ext_info_source_c;
   uint8_t participant_defined_c;
   char filler_1_s;
} ns_inst_series_basic_single_t;


/*   TRANSACTION TYPE = BU125, DA125  */
/*   NAMED STRUCT = 37306  */

typedef struct ns_inst_series_bo
{
   char isin_code_old_s [12];
   uint8_t tm_template_c;
   uint8_t tm_series_c;
   uint8_t accept_collateral_c;
   char filler_1_s;
} ns_inst_series_bo_t;


/*   TRANSACTION TYPE = BU124, BU125, DA124, DA125  */
/*   NAMED STRUCT = 37305  */

typedef struct ns_inst_series_ext1
{
   uint32_t series_sequence_number_u;
   char abbr_name_s [8];
   char stock_code_s [6];
   char filler_2_s [2];
} ns_inst_series_ext1_t;


/*   TRANSACTION TYPE = BU124, BU125, BU126, DA124, DA125, DA126  */
/*   NAMED STRUCT = 37310  */

typedef struct ns_inst_series_id
{
   int32_t orderbook_id_i;
} ns_inst_series_id_t;


/*   TRANSACTION TYPE = BU124, BU125, DA124, DA125  */
/*   NAMED STRUCT = 37303  */

typedef struct ns_inst_series_power
{
   char date_delivery_start_s [8];
   char date_delivery_stop_s [8];
} ns_inst_series_power_t;


/*   TRANSACTION TYPE = DA130, DA131  */
/*   NAMED STRUCT = 37601  */

typedef struct ns_inst_type_basic
{
   series_t series;
   uint32_t min_show_vol_u;
   uint16_t hidden_vol_meth_n;
   uint16_t pub_inf_id_n;
   char int_id_s [8];
   char name_s [32];
   uint8_t traded_c;
   uint8_t directed_trade_information_c;
   uint8_t public_deal_information_c;
   uint8_t pricing_method_c;
} ns_inst_type_basic_t;


/*   TRANSACTION TYPE = DA130, DA131  */
/*   NAMED STRUCT = 37603  */

typedef struct ns_inst_type_co
{
   int32_t option_price_limit_factor_i;
   uint8_t trade_report_price_check_c;
   char filler_3_s [3];
} ns_inst_type_co_t;


/*   TRANSACTION TYPE = DA130, DA131  */
/*   NAMED STRUCT = 37602  */

typedef struct ns_inst_type_secur
{
   char settlement_product_s [15];
   uint8_t maintain_positions_c;
   uint8_t post_trade_proc_c;
   uint8_t pos_handling_c;
   uint8_t pre_novation_collateral_check_c;
   uint8_t settlement_type_c;
   char filler_1_s;
} ns_inst_type_secur_t;


/*   TRANSACTION TYPE = BU90, DA90, DC90  */
/*   NAMED STRUCT = 37801  */

typedef struct ns_pre_trade_limit
{
   int64_t opt_long_total_credit_q;
   int64_t opt_short_total_credit_q;
   int64_t fut_total_buy_credit_q;
   int64_t fut_total_sell_credit_q;
   int64_t order_rate_limit_i;
   char ptl_suffix_s [64];
   char country_id_s [2];
   char ex_customer_s [5];
   char spons_user_name_s [32];
   char sponsored_client_country_id_s [2];
   char sponsored_client_ex_customer_s [5];
   int16_t warning_breach_lvl_n;
   int16_t not_breach_lvl_n;
   uint8_t enable_warn_email_c;
   uint8_t enable_not_email_c;
   uint8_t enable_breach_email_c;
   uint8_t db_operation_c;
   uint8_t intraday_c;
   char valid_from_date_s [8];
   uint8_t enable_restr_instr_c;
   uint8_t enable_def_user_c;
   uint8_t netted_consumption_c;
   uint8_t clearing_part_group_c;
   uint8_t parent_node_c;
   uint8_t ptl_blocked_c;
   char filler_3_s [3];
} ns_pre_trade_limit_t;


/*   TRANSACTION TYPE = BU90, DA90, DC90  */
/*   NAMED STRUCT = 37810  */

typedef struct ns_pre_trade_limit_coeff
{
   int32_t opt_long_coeff_i;
   int32_t opt_short_coeff_i;
   int32_t fut_coeff_i;
   uint16_t commodity_n;
   char valid_from_date_s [8];
   char filler_2_s [2];
} ns_pre_trade_limit_coeff_t;


/*   TRANSACTION TYPE = BU90, DA90  */
/*   NAMED STRUCT = 37805  */

typedef struct ns_pre_trade_limit_id
{
   char ptl_id_s [80];
} ns_pre_trade_limit_id_t;


/*   TRANSACTION TYPE = BU90, DA90, DC90  */
/*   NAMED STRUCT = 37804  */

typedef struct ns_pre_trade_limit_not
{
   char not_email_addr_s [128];
   char valid_from_date_s [8];
} ns_pre_trade_limit_not_t;


/*   TRANSACTION TYPE = BU90, DA90, DC90  */
/*   NAMED STRUCT = 37803  */

typedef struct ns_pre_trade_limit_param
{
   series_t series;
   int64_t max_order_size_q;
   int64_t open_buy_q;
   int64_t open_sell_q;
   int64_t traded_bought_q;
   int64_t traded_sold_q;
   int64_t traded_net_q;
   int64_t total_buy_q;
   int64_t total_sell_q;
   int64_t total_net_buy_q;
   int64_t total_net_sell_q;
   int32_t price_limit_i;
   uint8_t pre_trade_limit_param_unit_c;
   char valid_from_date_s [8];
   char filler_3_s [3];
} ns_pre_trade_limit_param_t;


/*   TRANSACTION TYPE = BU90, DA90, DC90  */
/*   NAMED STRUCT = 37802  */

typedef struct ns_pre_trade_limit_user
{
   user_code_t user_code;
   char valid_from_date_s [8];
} ns_pre_trade_limit_user_t;


/*   TRANSACTION TYPE = BU122, BU123, DA122, DA123  */
/*   NAMED STRUCT = 37102  */

typedef struct ns_price_tick
{
   tick_size_t tick_size;
   uint16_t dec_in_premium_n;
   char is_fractions_c;
   char filler_1_s;
} ns_price_tick_t;


/*   TRANSACTION TYPE = BU120, BU121, BU122, BU123, BU124, BU125, DA120, DA121, DA122, DA123, DA124, DA125  */
/*   NAMED STRUCT = 37002  */

typedef struct ns_remove
{
   series_t series;
} ns_remove_t;


/*   TRANSACTION TYPE = BI84  */
/*   NAMED STRUCT = 35007  */

typedef struct ns_report_create
{
   char report_name_s [64];
   char report_spec_s [5];
} ns_report_create_t;


/*   TRANSACTION TYPE = BI84  */
/*   NAMED STRUCT = 35008  */

typedef struct ns_report_param_create
{
   uint16_t param_no_n;
   char param_name_s [32];
   uint8_t param_type_c;
   uint8_t param_inp_value_c;
   char param_value_s [128];
} ns_report_param_create_t;


/*   TRANSACTION TYPE = BU120, BU121, DA120, DA121  */
/*   NAMED STRUCT = 37201  */

typedef struct ns_underlying_basic
{
   uint16_t commodity_n;
   uint16_t linked_commodity_n;
   uint16_t state_number_n;
   uint16_t dec_in_price_n;
   char com_id_s [6];
   char isin_code_s [12];
   char name_s [32];
   char base_cur_s [3];
   uint8_t deliverable_c;
   uint8_t underlying_type_c;
   uint8_t price_unit_c;
   uint8_t underlying_status_c;
   char underlying_issuer_s [6];
   char sector_code_s [4];
   uint8_t virtual_c;
   char country_id_s [2];
   char ext_provider_c;
   char external_id_s [40];
   uint8_t cur_unit_c;
   uint8_t db_operation_c;
   char filler_3_s [3];
} ns_underlying_basic_t;


/*   TRANSACTION TYPE = BU120, BU121, DA120, DA121  */
/*   NAMED STRUCT = 37205  */

typedef struct ns_underlying_ext1
{
   int32_t subscription_price_i;
   int32_t interest_rate_i;
   char member_circ_numb_s [4];
   char inv_scheme_c;
   char date_closing_s [8];
   char date_last_s [8];
   char filler_3_s [3];
} ns_underlying_ext1_t;


/*   BROADCAST TYPE = BO1  */

typedef struct ob_changes_id
{
   broadcast_type_t broadcast_type;
   changes_t changes;
   quad_word order_number_u;
   order_no_id_t order_no_id;
   party_t party;
} ob_changes_id_t;


/*   BROADCAST TYPE = BO2  */

typedef struct ob_changes_no_id
{
   broadcast_type_t broadcast_type;
   changes_t changes;
   quad_word order_number_u;
   order_no_id_t order_no_id;
} ob_changes_no_id_t;


/*   TRANSACTION TYPE = BD2, IA21, IA22  */
/*   NAMED STRUCT = 33031  */

typedef struct ob_levels_closing
{
   int32_t closing_price_i;
   int64_t open_balance_u;
} ob_levels_closing_t;


/*   TRANSACTION TYPE = IQ21, IQ22  */
/*   NAMED STRUCT = 33002  */

typedef struct ob_levels_id
{
   series_t series;
   uint32_t block_n;
} ob_levels_id_t;


/*   TRANSACTION TYPE = IA21, IA22  */
/*   NAMED STRUCT = 33032  */

typedef struct ob_levels_next_query
{
   uint16_t segment_number_n;
   uint8_t instance_c;
   uint8_t instance_next_c;
   series_next_t series_next;
} ob_levels_next_query_t;


/*   TRANSACTION TYPE = BO16, BO17, IA21, IA22  */
/*   NAMED STRUCT = 33004  */

typedef struct ob_levels_order_number
{
   quad_word order_number_bid_u;
   quad_word order_number_ask_u;
} ob_levels_order_number_t;


/*   TRANSACTION TYPE = IQ21, IQ22  */
/*   NAMED STRUCT = 33020  */

typedef struct ob_levels_query_data
{
   uint16_t segment_number_n;
   char filler_2_s [2];
} ob_levels_query_data_t;


/*   TRANSACTION TYPE = BO16, BO17, IA21, IA22  */
/*   NAMED STRUCT = 33005  */

typedef struct ob_levels_total_quantity
{
   int64_t total_quantity_bid_u;
   int64_t total_quantity_ask_u;
} ob_levels_total_quantity_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34902  */

typedef struct order_change_combined
{
   int64_t mp_quantity_i;
   int64_t total_volume_i;
   uint8_t item_number_c;
   uint8_t bid_or_ask_c;
   uint8_t change_reason_c;
   char filler_1_s;
} order_change_combined_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34919  */

typedef struct order_chg_sep_trans_ack
{
   int32_t trans_ack_i;
   order_change_separate_t order_change_separate;
} order_chg_sep_trans_ack_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34917  */

typedef struct order_info
{
   time_spec_t timestamp_in;
   time_spec_t timestamp_created;
   quad_word order_number_u;
   party_t party;
   order_t order;
   int64_t total_volume_i;
   int64_t display_quantity_i;
   int64_t orig_total_volume_i;
   int64_t orig_shown_quantity_i;
   uint32_t order_state_u;
} order_info_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34921  */

typedef struct order_leg_trade_info
{
   series_t series;
   match_id_t match_id;
   quad_word order_number_u;
   int32_t trade_price_i;
   int64_t trade_quantity_i;
   uint8_t item_number_c;
   uint8_t deal_source_c;
   uint8_t bid_or_ask_c;
   char filler_1_s;
} order_leg_trade_info_t;


/*   TRANSACTION TYPE = BO25, BO5, MO385, MO387  */
/*   NAMED STRUCT = 34804  */

typedef struct order_owner
{
   trading_code_t owner;
} order_owner_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34905  */

typedef struct order_price_change
{
   series_t series;
   quad_word order_number_u;
   int32_t premium_i;
   time_spec_t execution_timestamp;
   uint8_t bid_or_ask_c;
   uint8_t change_reason_c;
   char filler_2_s [2];
} order_price_change_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34904  */

typedef struct order_return_info
{
   int32_t trans_ack_i;
   quad_word order_number_u;
   originator_trading_code_t originator_trading_code;
   time_spec_t execution_timestamp;
} order_return_info_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34913  */

typedef struct order_state
{
   uint32_t order_state_u;
} order_state_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34910  */

typedef struct order_status
{
   char exchange_info_s [32];
   char customer_info_s [15];
   uint8_t open_close_req_c;
   int32_t premium_i;
   party_t party;
   int64_t orig_shown_quantity_i;
   int64_t orig_total_volume_i;
   int64_t rem_quantity_i;
   uint16_t transaction_number_n;
   uint16_t exch_order_type_n;
   give_up_member_t give_up_member;
   char ex_client_s [16];
   uint8_t order_type_c;
   char filler_3_s [3];
} order_status_t;


/*   TRANSACTION TYPE = BO25, BO5, MA476, MA92  */
/*   NAMED STRUCT = 34819  */

typedef struct order_submitter
{
   trading_code_t submitter;
} order_submitter_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34920  */

typedef struct order_trade_info
{
   match_id_t match_id;
   int32_t trade_price_i;
   int64_t trade_quantity_i;
   uint8_t item_number_c;
   uint8_t deal_source_c;
   uint8_t bid_or_ask_c;
   char filler_1_s;
} order_trade_info_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34004  */

typedef struct order_trans
{
   transaction_type_t transaction_type;
   series_t series;
   order_var_t order_var;
   char exchange_info_s [32];
   give_up_member_t give_up_member;
} order_trans_t;


/*   TRANSACTION TYPE = KA1, KB1, KB14, KC1  */
/*   NAMED STRUCT = 38001  */

typedef struct otc_base_trade_report
{
   party_t party;
   account_t account;
   account_t give_up_account;
   series_t series;
   char passthrough_s [32];
   char settlement_date_s [8];
   char asof_date_s [8];
   char participant_info_s [80];
   char name_s [32];
   uint8_t bought_or_sold_c;
   uint8_t trade_report_category_c;
   char private_match_field_s [52];
   char give_up_text_s [30];
   char filler_4_s [4];
} otc_base_trade_report_t;


/*   TRANSACTION TYPE = JQ71  */
/*   NAMED STRUCT = 65  */

typedef struct otc_cash_flow_base
{
   account_t account;
   series_t series;
   char description_s [40];
   int32_t sequence_number_i;
} otc_cash_flow_base_t;


/*   TRANSACTION TYPE = JQ71  */
/*   NAMED STRUCT = 66  */

typedef struct otc_cash_flow_info
{
   uint64_t trade_report_nbr_q;
   int64_t notional_amount_q;
   uint64_t consideration_u;
   int32_t interest_rate_i;
   int32_t spread_i;
   uint16_t dec_in_nominal_n;
   uint16_t dec_in_consideration_n;
   uint16_t dec_in_rate_n;
   uint16_t dec_in_spread_n;
   uint16_t days_in_period_n;
   uint16_t days_per_year_n;
   char passthrough_s [32];
   char start_date_s [8];
   char end_date_s [8];
   char payment_date_s [8];
   char currency_s [3];
   uint8_t fixed_or_float_c;
   uint8_t pay_or_receive_c;
   uint8_t otc_cash_flow_type_c;
   uint8_t business_day_conv_c;
   uint8_t basis_swap_relation_c;
   char reset_date_s [8];
   int32_t fixing_value_i;
   char trade_clearing_date [8];
   int32_t sequence_number_i;
   int64_t accumulated_consideration_q;
   int64_t estimated_accumulated_consideration_q;
   char estimated_consideration_date_s [8];
   char is_flow_reset_c;
   char filler_3_s [3];
} otc_cash_flow_info_t;


/*   TRANSACTION TYPE = KA1, KB1, KB14  */
/*   NAMED STRUCT = 83  */

typedef struct otc_clearing_info
{
   account_t position_account;
   char clearing_date_s [8];
   char orig_clearing_date_s [8];
} otc_clearing_info_t;


/*   TRANSACTION TYPE = KA1, KB1, KB14  */
/*   NAMED STRUCT = 38004  */

typedef struct otc_fra_data
{
   series_t float_rate_series;
   int64_t fixed_consideration_q;
   int64_t float_consideration_q;
   int64_t pay_amount_q;
   int32_t float_interest_rate_i;
} otc_fra_data_t;


/*   TRANSACTION TYPE = KA1, KB1, KB14, KC1  */
/*   NAMED STRUCT = 38003  */

typedef struct otc_fra_trade_report
{
   series_t float_rate_index;
   int64_t notional_amount_q;
   int32_t fixed_interest_rate_i;
   char float_rate_fixing_date_s [8];
   char date_termination_s [8];
   uint8_t day_count_conv_c;
   char filler_3_s [3];
} otc_fra_trade_report_t;


/*   TRANSACTION TYPE = KB14  */
/*   NAMED STRUCT = 38019  */

typedef struct otc_give_up_info
{
   account_t account;
   int32_t give_up_number_i;
   char give_up_text_s [30];
   char take_up_or_reject_text_s [30];
} otc_give_up_info_t;


/*   TRANSACTION TYPE = KB14  */
/*   NAMED STRUCT = 38018  */

typedef struct otc_give_up_state
{
   uint8_t give_up_state_c;
   uint8_t give_up_sub_state_c;
   uint8_t give_up_reason_c;
} otc_give_up_state_t;


/*   TRANSACTION TYPE = KA1, KB1, KB14  */
/*   NAMED STRUCT = 38005  */

typedef struct otc_irs_data
{
   uint16_t flow_version_n;
   char delivery_unit_date_s [8];
   uint8_t termination_state_c;
   char filler_3_s [3];
} otc_irs_data_t;


/*   TRANSACTION TYPE = KA1, KB1, KB14, KC1  */
/*   NAMED STRUCT = 38006  */

typedef struct otc_irs_trade_report
{
   payment_t upfront;
   char date_termination_s [8];
   int64_t notional_amount_q;
   uint8_t business_day_conv_c;
   uint8_t rate_reset_c;
   uint8_t reset_days_c;
   uint8_t payment_set_c;
} otc_irs_trade_report_t;


/*   TRANSACTION TYPE = KB10  */
/*   NAMED STRUCT = 38012  */

typedef struct otc_operation_info
{
   int32_t sequence_number_i;
   uint8_t trade_operation_c;
   char filler_3_s [3];
} otc_operation_info_t;


/*   TRANSACTION TYPE = JQ71  */
/*   NAMED STRUCT = 50020  */

typedef struct otc_option
{
   series_t opt_series;
   char premium_settlement_date_s [8];
   int32_t premium_i;
   char expiration_date_s [8];
   uint8_t bought_or_sold_c;
   char filler_3_s [3];
} otc_option_t;


/*   TRANSACTION TYPE = KB10  */
/*   NAMED STRUCT = 38014  */

typedef struct otc_trade
{
   account_t account;
   account_t pos_account;
   series_t series;
   uint64_t trade_report_number_q;
   int64_t trade_quantity_i;
   int32_t trade_price_i;
   int32_t trade_clean_price;
   uint8_t bought_or_sold_c;
   char filler_3_s [3];
} otc_trade_t;


/*   TRANSACTION TYPE = KB10  */
/*   NAMED STRUCT = 38013  */

typedef struct otc_trade_operation
{
   account_t account;
   trading_code_t trading_code;
   uint64_t trade_report_number_q;
   uint64_t party_trade_report_number_q;
   int64_t trade_operation_number_q;
   char participant_info_s [80];
   uint8_t trade_report_state_c;
   uint8_t trade_report_sub_state_c;
   uint8_t trade_report_reason_c;
   uint8_t trade_operation_c;
} otc_trade_operation_t;


/*   TRANSACTION TYPE = KA1, KB1, KB14  */
/*   NAMED STRUCT = 38002  */

typedef struct otc_trade_report_data
{
   trading_code_t trading_code;
   user_code_t user_code;
   auth_by_whom_t auth_by_whom;
   uint32_t delivery_unit_u;
   uint32_t trade_report_type_i;
   uint64_t trade_report_nbr_q;
   uint64_t party_trade_report_nbr_q;
   int32_t sequence_number_i;
   uint32_t netting_req_nbr_u;
   uint32_t pay_calc_req_nbr_u;
   int32_t deal_number_i;
   uint16_t trade_report_version_n;
   char timestamp_date_s [8];
   char timestamp_time_s [6];
   char isin_code_s [12];
   uint8_t trade_report_state_c;
   uint8_t trade_report_sub_state_c;
   uint8_t trade_report_reason_c;
   uint8_t authorization_state_c;
   trading_code_t reported_by;
   uint8_t affirmation_state_c;
   trading_code_t affirmed_by;
   uint8_t trade_type_c;
   char filler_2_s [2];
} otc_trade_report_data_t;


/*   BROADCAST TYPE = BI26  */

typedef struct pay_note_info_ready
{
   broadcast_type_t broadcast_type;
   int32_t info_type_i;
   char date_s [8];
   char clh_id_s [12];
   char sent_date_s [8];
   char sent_time_s [6];
   char clearing_date_s [8];
   char filler_2_s [2];
} pay_note_info_ready_t;


/*   TRANSACTION TYPE = CD54  */

typedef struct position_closeout
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t items_n;
   char filler_2_s [2];
   position_closeout_item_t item [950];
} position_closeout_t;


/*   TRANSACTION TYPE = CA54  */

typedef struct position_closeout_status
{
   transaction_type_t transaction_type;
   uint16_t items_n;
   char filler_2_s [2];
   position_closeout_status_item_t item [950];
} position_closeout_status_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34002  */

typedef struct price_2_trans
{
   transaction_type_t transaction_type;
   series_t series;
   int32_t bid_premium_i;
   int32_t ask_premium_i;
   quad_word order_number_bid_u;
   quad_word order_number_ask_u;
   int64_t bid_quantity_i;
   int64_t ask_quantity_i;
   uint32_t block_n;
   uint16_t time_validity_n;
   char ex_client_s [16];
   char filler_2_s [2];
} price_2_trans_t;


/*   TRANSACTION TYPE = BO16, BO17, IA21, IA22  */
/*   NAMED STRUCT = 33051  */

typedef struct price_depth
{
   int32_t price_i;
   uint8_t price_depth_position_c;
   uint8_t price_depth_operator_c;
   uint8_t bid_or_ask_c;
   char filler_1_s;
} price_depth_t;


/*   TRANSACTION TYPE = BO16, BO17  */
/*   NAMED STRUCT = 33056  */

typedef struct price_depth_delete_levels
{
   uint8_t price_depth_position_c;
   uint8_t levels_to_delete_c;
   uint8_t bid_or_ask_c;
   char filler_1_s;
} price_depth_delete_levels_t;


/*   TRANSACTION TYPE = BO16, BO17, IA21, IA22  */
/*   NAMED STRUCT = 33050  */

typedef struct price_depth_series
{
   series_t series;
   uint32_t synchronization_number_u;
   uint32_t block_n;
   uint8_t premium_levels_c;
   uint8_t demands_populated_c;
   char filler_2_s [2];
   uint32_t reserved1_u;
} price_depth_series_t;


/*   TRANSACTION TYPE = BO16, BO17, IA21, IA22  */
/*   NAMED STRUCT = 33055  */

typedef struct price_depth_tot_orders
{
   uint32_t total_no_of_bid_orders_u;
   uint32_t total_no_of_ask_orders_u;
} price_depth_tot_orders_t;


/*   TRANSACTION TYPE = BO16, BO17, IA21, IA22  */
/*   NAMED STRUCT = 33054  */

typedef struct price_depth_with_orders
{
   int32_t price_i;
   uint32_t no_of_orders_u;
   uint8_t price_depth_position_c;
   uint8_t price_depth_operator_c;
   uint8_t bid_or_ask_c;
   char filler_1_s;
} price_depth_with_orders_t;


/*   TRANSACTION TYPE = BO16, BO17, IA21, IA22  */
/*   NAMED STRUCT = 33052  */

typedef struct price_depth_with_volume
{
   int32_t price_i;
   int64_t quantity_u;
   uint8_t hidden_quantity_c;
   uint8_t price_depth_position_c;
   uint8_t price_depth_operator_c;
   uint8_t bid_or_ask_c;
} price_depth_with_volume_t;


/*   TRANSACTION TYPE = BO16, BO17, IA21, IA22  */
/*   NAMED STRUCT = 33053  */

typedef struct price_depth_with_volume_orders
{
   int32_t price_i;
   int64_t quantity_u;
   uint32_t no_of_orders_u;
   uint8_t hidden_quantity_c;
   uint8_t price_depth_position_c;
   uint8_t price_depth_operator_c;
   uint8_t bid_or_ask_c;
} price_depth_with_volume_orders_t;


/*   BROADCAST TYPE = BL58  */

typedef struct price_limit_trigger
{
   broadcast_type_t broadcast_type;
   series_t series;
   time_spec_t timestamp;
   int32_t lower_limit_i;
   int32_t upper_limit_i;
   int32_t next_lower_limit_i;
   int32_t next_upper_limit_i;
   int32_t cool_off_time_i;
   uint8_t tier_c;
   char price_limit_unit_c;
   char filler_2_s [2];
} price_limit_trigger_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34003  */

typedef struct price_trans
{
   transaction_type_t transaction_type;
   series_t series;
   order_var_t order_var;
   quad_word order_number_u;
   give_up_member_t give_up_member;
} price_trans_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34103  */

typedef struct price_trans_p
{
   transaction_type_t transaction_type;
   series_t series;
   trading_code_t trading_code;
   order_var_t order_var;
   quad_word order_number_u;
   give_up_member_t give_up_member;
} price_trans_p_t;


/*   TRANSACTION TYPE = JQ71  */
/*   NAMED STRUCT = 50019  */

typedef struct private_price_list_id
{
   char private_price_list_id_s [32];
} private_price_list_id_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34814  */

typedef struct quantity_condition
{
   int64_t minimum_quantity_i;
} quantity_condition_t;


/*   TRANSACTION TYPE = CQ117  */

typedef struct query_aat_connection
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   uint8_t connect_type_c;
   char filler_1_s;
   participant_t participant;
   char acc_access_type_s [64];
   char search_id_s [64];
} query_aat_connection_t;


/*   TRANSACTION TYPE = CQ128, CQ38  */

typedef struct query_account
{
   transaction_type_t transaction_type;
   series_t series;
   account_t account;
   uint16_t segment_number_n;
   uint8_t query_on_date_c;
   char date_s [8];
   char filler_1_s;
} query_account_t;


/*   TRANSACTION TYPE = DQ13  */

typedef struct query_account_fee_type
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_account_fee_type_t;


/*   TRANSACTION TYPE = CQ19  */

typedef struct query_account_prop
{
   transaction_type_t transaction_type;
   series_t series;
   account_t account;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_account_prop_t;


/*   TRANSACTION TYPE = DQ12, DQ134  */

typedef struct query_account_type
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_account_type_t;


/*   TRANSACTION TYPE = DQ34  */

typedef struct query_account_type_rule
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_account_type_rule_t;


/*   TRANSACTION TYPE = CQ116  */

typedef struct query_acc_access_type
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
   ex_user_code_t ex_user_code;
   char acc_access_type_s [64];
   account_t account;
   int32_t only_wildcard_i;
} query_acc_access_type_t;


/*   TRANSACTION TYPE = CQ132  */

typedef struct query_acc_access_type_ext
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
   acc_access_type_key_t key;
} query_acc_access_type_ext_t;


/*   TRANSACTION TYPE = TR71  */

typedef struct query_amended_trades
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_amended_trades_t;


/*   TRANSACTION TYPE = CQ53  */

typedef struct query_api_delivery
{
   transaction_type_t transaction_type;
   series_t series;
   char from_date_s [8];
   int32_t sequence_first_i;
   char to_date_s [8];
   int32_t sequence_last_i;
} query_api_delivery_t;


/*   TRANSACTION TYPE = CQ77  */

typedef struct query_api_give_up
{
   transaction_type_t transaction_type;
   series_t series;
   char from_date_s [8];
   int32_t sequence_first_i;
   char to_date_s [8];
   int32_t sequence_last_i;
} query_api_give_up_t;


/*   TRANSACTION TYPE = CQ11  */

typedef struct query_api_trade
{
   transaction_type_t transaction_type;
   series_t series;
   char from_date_s [8];
   int32_t sequence_first_i;
   char to_date_s [8];
   int32_t sequence_last_i;
} query_api_trade_t;


/*   TRANSACTION TYPE = DQ58  */

typedef struct query_authorized_report
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char country_id_s [2];
   char ex_customer_s [5];
   char filler_3_s [3];
} query_authorized_report_t;


/*   TRANSACTION TYPE = CQ36  */

typedef struct query_average_price_trade
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
   int32_t trade_number_i;
} query_average_price_trade_t;


/*   TRANSACTION TYPE = UQ10  */

typedef struct query_bi26_signals_sent
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   char date_s [8];
   char filler_2_s [2];
} query_bi26_signals_sent_t;


/*   TRANSACTION TYPE = UQ22  */

typedef struct query_bi26_signals_sent_cl
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   char clearing_date_s [8];
   char filler_2_s [2];
} query_bi26_signals_sent_cl_t;


/*   TRANSACTION TYPE = UQ13  */

typedef struct query_bi27_broadcasts_sent
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   char sent_date_s [8];
   char filler_2_s [2];
} query_bi27_broadcasts_sent_t;


/*   TRANSACTION TYPE = UQ20  */

typedef struct query_bi73_signals_sent
{
   transaction_type_t transaction_type;
   search_series_t search_series;
   uint16_t segment_number_n;
   char business_date_s [8];
   char clearing_date_s [8];
   uint16_t seq_num_srm_n;
} query_bi73_signals_sent_t;


/*   TRANSACTION TYPE = UQ9  */

typedef struct query_bi7_signals_sent
{
   transaction_type_t transaction_type;
   search_series_t search_series;
   uint16_t segment_number_n;
   char business_date_s [8];
   uint16_t seq_num_srm_n;
} query_bi7_signals_sent_t;


/*   TRANSACTION TYPE = UQ21  */

typedef struct query_bi7_signals_sent_cl
{
   transaction_type_t transaction_type;
   search_series_t search_series;
   uint16_t segment_number_n;
   char clearing_date_s [8];
   uint16_t seq_num_srm_n;
} query_bi7_signals_sent_cl_t;


/*   TRANSACTION TYPE = UQ14  */

typedef struct query_bi81_broadcasts_sent
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   uint8_t message_information_type_c;
   uint8_t message_priority_c;
   char date_s [8];
   uint32_t from_sequence_number_u;
   uint32_t to_sequence_number_u;
   search_series_t search_series;
   uint8_t update_status_note_c;
   char filler_3_s [3];
} query_bi81_broadcasts_sent_t;


/*   TRANSACTION TYPE = MQ99  */

typedef struct query_block_size
{
   transaction_type_t transaction_type;
   series_t series;
} query_block_size_t;


/*   TRANSACTION TYPE = DQ6  */

typedef struct query_broker
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char country_id_s [2];
   char ex_customer_s [5];
   char filler_3_s [3];
} query_broker_t;


/*   TRANSACTION TYPE = UQ12  */

typedef struct query_business_date
{
   transaction_type_t transaction_type;
} query_business_date_t;


/*   TRANSACTION TYPE = DQ28  */

typedef struct query_central_group
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_central_group_t;


/*   TRANSACTION TYPE = CQ68  */

typedef struct query_clearing_date
{
   transaction_type_t transaction_type;
   series_t series;
   search_series_t search_series;
} query_clearing_date_t;


/*   TRANSACTION TYPE = CQ123  */

typedef struct query_closeout_log
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
   account_t account;
   char series_id_s [32];
   char from_date_s [8];
   char from_time_s [6];
   char to_date_s [8];
   char to_time_s [6];
} query_closeout_log_t;


/*   TRANSACTION TYPE = FQ1  */

typedef struct query_collateral
{
   transaction_type_t transaction_type;
   series_t series;
   account_t account;
   char series_id_s [32];
   uint16_t segment_number_n;
   uint8_t collateral_type_c;
   uint8_t state_c;
} query_collateral_t;


/*   TRANSACTION TYPE = FQ17  */

typedef struct query_collateral_evaluation_run
{
   transaction_type_t transaction_type;
   series_t series;
   margin_account_t margin_account;
   char clh_id_s [12];
   char valuation_date_s [8];
   char created_date_s [8];
   char from_time_s [6];
   char to_time_s [6];
   uint16_t segment_number_n;
   uint8_t collateral_evaluation_type_c;
   uint8_t is_final_c;
   uint8_t is_intraday_c;
   char filler_3_s [3];
} query_collateral_evaluation_run_t;


/*   TRANSACTION TYPE = FQ16  */

typedef struct query_collateral_information
{
   transaction_type_t transaction_type;
   series_t series;
   char clh_id_s [12];
   margin_account_t margin_account;
   uint16_t segment_number_n;
   char filler_2_s [2];
   char valuation_date_s [8];
   uint32_t request_nbr_u;
} query_collateral_information_t;


/*   TRANSACTION TYPE = FQ20  */

typedef struct query_collateral_transaction
{
   transaction_type_t transaction_type;
   series_t series;
   account_t collateral_account;
   uint32_t instruction_nbr_u;
   uint32_t coll_payment_nbr_u;
   uint32_t ext_coll_payment_nbr_u;
   char from_date_s [8];
   char to_date_s [8];
   char from_time_s [6];
   char to_time_s [6];
   char instr_ref_s [16];
   char cancel_ref_s [16];
   char series_id_s [32];
   char account_number_s [34];
   char bic_code_s [15];
   char clh_bank_account_number_s [34];
   char clh_bank_bic_code_s [15];
   uint16_t segment_number_n;
   uint16_t items_n;
   uint8_t collateral_transaction_type_c;
   char filler_1_s;
   query_collateral_transaction_item_t item [20];
} query_collateral_transaction_t;


/*   TRANSACTION TYPE = FQ24  */

typedef struct query_collateral_transaction_specific_version
{
   transaction_type_t transaction_type;
   series_t series;
   uint64_t collateral_transaction_nbr_q;
   uint32_t request_nbr_u;
   char valuation_date_s [8];
   char clh_id_s [12];
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_collateral_transaction_specific_version_t;


/*   TRANSACTION TYPE = FQ21  */

typedef struct query_collateral_transaction_version
{
   transaction_type_t transaction_type;
   series_t series;
   uint64_t collateral_transaction_nbr_q;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_collateral_transaction_version_t;


/*   TRANSACTION TYPE = FQ2  */

typedef struct query_collateral_version
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
   uint64_t collateral_nbr_q;
} query_collateral_version_t;


/*   TRANSACTION TYPE = FQ14  */

typedef struct query_coll_val_per_series
{
   transaction_type_t transaction_type;
   series_t series;
   account_t collateral_account;
   margin_account_t margin_account;
   uint32_t request_nbr_u;
   char clh_id_s [12];
   char series_id_s [32];
   char valuation_date_s [8];
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_coll_val_per_series_t;


/*   TRANSACTION TYPE = FQ15  */

typedef struct query_coll_val_per_val_group
{
   transaction_type_t transaction_type;
   series_t series;
   margin_account_t margin_account;
   uint32_t request_nbr_u;
   char clh_id_s [12];
   char vag_id_s [12];
   char valuation_date_s [8];
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_coll_val_per_val_group_t;


/*   TRANSACTION TYPE = DQ126, DQ136, DQ5, DQ77  */

typedef struct query_combo
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_combo_t;


/*   TRANSACTION TYPE = CQ64  */

typedef struct query_commission
{
   transaction_type_t transaction_type;
   series_t series;
   party_t party;
   uint8_t send_receive_c;
   char filler_3_s [3];
} query_commission_t;


/*   TRANSACTION TYPE = CQ62  */

typedef struct query_conf_give_up_req_items
{
   transaction_type_t transaction_type;
   series_t series;
   int32_t give_up_number_i;
} query_conf_give_up_req_items_t;


/*   TRANSACTION TYPE = DQ15  */

typedef struct query_converted_series
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   uint16_t adjust_ident_n;
} query_converted_series_t;


/*   TRANSACTION TYPE = ML59  */

typedef struct query_cool_off_period_ended
{
   transaction_type_t transaction_type;
   series_t series;
   uint8_t only_this_series_c;
   char filler_3_s [3];
} query_cool_off_period_ended_t;


/*   TRANSACTION TYPE = DQ53  */

typedef struct query_corp_action
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_corp_action_t;


/*   TRANSACTION TYPE = DQ33  */

typedef struct query_currency
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_currency_t;


/*   TRANSACTION TYPE = CQ129  */

typedef struct query_currency_ranking
{
   transaction_type_t transaction_type;
   series_t series;
   currency_ranking_key_t key;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_currency_ranking_t;


/*   TRANSACTION TYPE = CQ131  */

typedef struct query_currency_ranking_accounts
{
   transaction_type_t transaction_type;
   series_t series;
   participant_t participant;
   char currency_ranking_id_s [32];
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_currency_ranking_accounts_t;


/*   TRANSACTION TYPE = CQ130  */

typedef struct query_currency_ranking_connections
{
   transaction_type_t transaction_type;
   series_t series;
   account_t account;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_currency_ranking_connections_t;


/*   TRANSACTION TYPE = DQ46  */

typedef struct query_deal_source
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_deal_source_t;


/*   TRANSACTION TYPE = DQ120, DQ121, DQ122, DQ123, DQ124, DQ125  */

typedef struct query_delta
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
   int64_t download_ref_number_q;
   time_spec_t full_answer_timestamp;
} query_delta_t;


/*   TRANSACTION TYPE = ML2153, ML2156  */

typedef struct query_delta_limit_trans
{
   transaction_type_t transaction_type;
   series_t series;
   uint8_t only_this_series_c;
   char filler_3_s [3];
} query_delta_limit_trans_t;


/*   TRANSACTION TYPE = JQ31  */

typedef struct query_dh_margin_components
{
   transaction_type_t transaction_type;
   series_t series;
   account_t account;
   char clh_id_s [12];
   char business_date_s [8];
   int32_t sequence_number_n;
   uint16_t segment_number_n;
   uint8_t run_type_c;
   char filler_1_s;
} query_dh_margin_components_t;


/*   TRANSACTION TYPE = CQ22  */

typedef struct query_error_msg
{
   transaction_type_t transaction_type;
   series_t series;
   search_series_t search_series;
   account_t account;
   uint32_t error_id_u;
   uint16_t segment_number_n;
   char from_date_s [8];
   char to_date_s [8];
   char from_time_s [6];
   char to_time_s [6];
   char filler_2_s [2];
} query_error_msg_t;


/*   TRANSACTION TYPE = DQ78  */

typedef struct query_exception_days
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_exception_days_t;


/*   TRANSACTION TYPE = DQ24  */

typedef struct query_exchange_dq24
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_exchange_dq24_t;


/*   TRANSACTION TYPE = RQ31  */

typedef struct query_exchange_rate
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char date_s [8];
   char filler_2_s [2];
} query_exchange_rate_t;


/*   TRANSACTION TYPE = CQ21  */

typedef struct query_exercise_req
{
   transaction_type_t transaction_type;
   series_t series;
   search_series_t search_series;
   account_t account;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_exercise_req_t;


/*   TRANSACTION TYPE = CQ100  */

typedef struct query_fixing_dates
{
   transaction_type_t transaction_type;
   series_t series;
} query_fixing_dates_t;


/*   TRANSACTION TYPE = CQ8  */

typedef struct query_fixing_val
{
   transaction_type_t transaction_type;
   series_t series;
   search_series_t search_series;
   uint16_t segment_number_n;
   char date_s [8];
   char filler_2_s [2];
} query_fixing_val_t;


/*   TRANSACTION TYPE = CQ61  */

typedef struct query_give_up_request
{
   transaction_type_t transaction_type;
   series_t series;
   party_t party;
   uint32_t ext_trade_number_u;
   uint16_t segment_number_n;
   uint8_t state_c;
   uint8_t buy_or_sell_c;
   uint8_t send_or_receive_c;
   char created_date_s [8];
   char series_id_s [32];
   char country_id_s [2];
   char ex_customer_s [5];
   char give_up_text_s [30];
   char filler_2_s [2];
} query_give_up_request_t;


/*   TRANSACTION TYPE = RQ36  */

typedef struct query_greeks
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char date_s [8];
   uint8_t intra_day2_c;
   char filler_1_s;
   uint16_t marg_run_nbr_n;
   uint16_t marg_call_nbr_n;
} query_greeks_t;


/*   TRANSACTION TYPE = DQ47  */

typedef struct query_haircut
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_haircut_t;


/*   TRANSACTION TYPE = IQ21, IQ22  */

typedef struct query_hdr
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t items_n;
   uint16_t size_n;
} query_hdr_t;


/*   TRANSACTION TYPE = DQ130, DQ131, DQ22, DQ3  */

typedef struct query_instrument
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_instrument_t;


/*   TRANSACTION TYPE = DQ10, DQ20  */

typedef struct query_instrument_class
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_instrument_class_t;


/*   TRANSACTION TYPE = DQ8  */

typedef struct query_instrument_group
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_instrument_group_t;


/*   TRANSACTION TYPE = UQ15  */

typedef struct query_instrument_status
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   uint16_t state_level_e;
} query_instrument_status_t;


/*   TRANSACTION TYPE = ML1  */

typedef struct query_limit_trans
{
   transaction_type_t transaction_type;
   series_t series;
   uint8_t only_this_series_c;
   char filler_3_s [3];
} query_limit_trans_t;


/*   TRANSACTION TYPE = LQ3  */

typedef struct query_list_ver
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char date_s [8];
   char report_version_s [3];
   char filler_3_s [3];
   int32_t info_type_i;
} query_list_ver_t;


/*   TRANSACTION TYPE = LR5  */

typedef struct query_list_ver_nrs
{
   transaction_type_t transaction_type;
   uint16_t segment_number_n;
   char file_name_s [80];
} query_list_ver_nrs_t;


/*   TRANSACTION TYPE = SQ2  */

typedef struct query_manual_payments
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
   char date_s [8];
} query_manual_payments_t;


/*   TRANSACTION TYPE = RQ21  */

typedef struct query_margin_acc
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
   char date_s [8];
   account_t account;
   char cust_bank_id_s [12];
} query_margin_acc_t;


/*   TRANSACTION TYPE = FQ19  */

typedef struct query_margin_collateral_evaluation_sgx
{
   transaction_type_t transaction_type;
   series_t series;
   margin_account_t margin_account;
   uint32_t request_nbr_u;
   uint16_t segment_number_n;
   char clh_id_s [12];
   char valuation_date_s [8];
   char currency_s [3];
   char filler_3_s [3];
} query_margin_collateral_evaluation_sgx_t;


/*   TRANSACTION TYPE = RQ35  */

typedef struct query_margin_data_used
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char date_s [8];
   uint8_t intra_day2_c;
   char filler_1_s;
   uint16_t marg_run_nbr_n;
   uint16_t marg_call_nbr_n;
} query_margin_data_used_t;


/*   TRANSACTION TYPE = RQ7  */

typedef struct query_margin_detail
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char date_s [8];
   uint8_t intra_day2_c;
   char filler_1_s;
   account_t account;
   uint16_t marg_run_nbr_n;
   uint16_t marg_call_nbr_n;
} query_margin_detail_t;


/*   TRANSACTION TYPE = RQ6  */

typedef struct query_margin_ext
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char date_s [8];
   char filler_2_s [2];
} query_margin_ext_t;


/*   TRANSACTION TYPE = RQ23  */

typedef struct query_margin_mem
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char date_s [8];
   char filler_2_s [2];
} query_margin_mem_t;


/*   TRANSACTION TYPE = RQ20  */

typedef struct query_margin_pa_acc
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
   char date_s [8];
   account_t account;
   char cust_bank_id_s [12];
} query_margin_pa_acc_t;


/*   TRANSACTION TYPE = RQ122, RQ22  */

typedef struct query_margin_prop
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char date_s [8];
   uint8_t intra_day2_c;
   uint8_t incl_marg_calc_acc_c;
   uint16_t marg_run_nbr_n;
   uint16_t marg_call_nbr_n;
   account_t account;
} query_margin_prop_t;


/*   TRANSACTION TYPE = JQ54, JQ55  */

typedef struct query_margin_requirement_account
{
   transaction_type_t transaction_type;
   series_t series;
   char clh_id_s [12];
   account_t mra_account;
   int32_t sequence_number_n;
   uint16_t segment_number_n;
   char business_date_s [8];
   uint8_t run_type_c;
   uint8_t instrument_or_risk_currency_c;
} query_margin_requirement_account_t;


/*   TRANSACTION TYPE = JQ7  */

typedef struct query_margin_results_internal
{
   transaction_type_t transaction_type;
   series_t series;
   account_t account;
   char margin_date_s [8];
   char clh_id_s [12];
   int32_t sequence_number_n;
   uint16_t segment_number_n;
   uint8_t run_type_rm_internal_c;
   uint8_t margin_calculation_type_c;
} query_margin_results_internal_t;


/*   TRANSACTION TYPE = RQ1  */

typedef struct query_margin_series_param
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_margin_series_param_t;


/*   TRANSACTION TYPE = RQ3  */

typedef struct query_margin_series_param_ext
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char date_s [8];
   uint8_t intra_day2_c;
   char filler_1_s;
   uint16_t marg_run_nbr_n;
   uint16_t marg_call_nbr_n;
} query_margin_series_param_ext_t;


/*   TRANSACTION TYPE = RQ41  */

typedef struct query_margin_ulg_price
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char date_s [8];
   char filler_2_s [2];
} query_margin_ulg_price_t;


/*   TRANSACTION TYPE = JQ1  */

typedef struct query_marg_calc_runs
{
   transaction_type_t transaction_type;
   series_t series;
   char business_date_s [8];
   uint16_t segment_number_n;
   uint8_t run_type_c;
   char clh_id_s [12];
   char filler_1_s;
} query_marg_calc_runs_t;


/*   TRANSACTION TYPE = RQ72  */

typedef struct query_marg_sim_add_trade
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char sub_user_s [32];
   char filler_2_s [2];
} query_marg_sim_add_trade_t;


/*   TRANSACTION TYPE = DQ23, DQ7  */

typedef struct query_market
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_market_t;


/*   TRANSACTION TYPE = DQ57  */

typedef struct query_member_obligation
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   uint8_t on_behalf_of_type_c;
   char filler_1_s;
} query_member_obligation_t;


/*   TRANSACTION TYPE = FQ22  */

typedef struct query_missing_collateral_transaction
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
   int32_t sequence_first_i;
   int32_t sequence_last_i;
   char clearing_date_s [8];
} query_missing_collateral_transaction_t;


/*   TRANSACTION TYPE = CQ52  */

typedef struct query_missing_delivery
{
   transaction_type_t transaction_type;
   series_t series;
   int32_t sequence_first_i;
   int32_t sequence_last_i;
   char date_s [8];
} query_missing_delivery_t;


/*   TRANSACTION TYPE = CQ76  */

typedef struct query_missing_give_up
{
   transaction_type_t transaction_type;
   series_t series;
   int32_t sequence_first_i;
   int32_t sequence_last_i;
   char date_s [8];
} query_missing_give_up_t;


/*   TRANSACTION TYPE = CQ10  */

typedef struct query_missing_trade
{
   transaction_type_t transaction_type;
   series_t series;
   int32_t sequence_first_i;
   int32_t sequence_last_i;
   char date_s [8];
} query_missing_trade_t;


/*   TRANSACTION TYPE = CQ39  */

typedef struct query_missing_trade_change
{
   transaction_type_t transaction_type;
   series_t series;
   uint8_t instance_c;
   char filler_3_s [3];
   int32_t sequence_first_i;
   int32_t sequence_last_i;
   char date_s [8];
} query_missing_trade_change_t;


/*   TRANSACTION TYPE = DQ87  */

typedef struct query_mm_protection
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_mm_protection_t;


/*   TRANSACTION TYPE = DQ18  */

typedef struct query_non_trading_days
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_non_trading_days_t;


/*   TRANSACTION TYPE = DQ50  */

typedef struct query_non_trad_settl_days
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_non_trad_settl_days_t;


/*   TRANSACTION TYPE = CQ20  */

typedef struct query_open_interest
{
   transaction_type_t transaction_type;
   series_t series;
   search_series_t search_series;
   uint16_t segment_number_n;
   char date_s [8];
   char filler_2_s [2];
} query_open_interest_t;


/*   TRANSACTION TYPE = CQ72  */

typedef struct query_open_interest_ext
{
   transaction_type_t transaction_type;
   series_t series;
   search_series_t search_series;
   uint16_t segment_number_n;
   char filler_2_s [2];
   char date_s [8];
} query_open_interest_ext_t;


/*   TRANSACTION TYPE = MQ92  */

typedef struct query_order_private_filter
{
   transaction_type_t transaction_type;
   series_t series;
   series_t search_series;
   whose_t whose;
   quad_word order_number_u;
   int32_t order_filter_i;
   uint16_t stp_key_i;
   uint8_t bid_or_ask_c;
   char filler_1_s;
} query_order_private_filter_t;


/*   TRANSACTION TYPE = MQ476  */

typedef struct query_order_private_filter_p
{
   transaction_type_t transaction_type;
   series_t series;
   series_t search_series;
   whose_t whose;
   quad_word order_number_u;
   int32_t order_filter_i;
   uint16_t stp_key_i;
   uint8_t bid_or_ask_c;
   char filler_1_s;
} query_order_private_filter_p_t;


/*   TRANSACTION TYPE = UQ1  */

typedef struct query_partition
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_partition_t;


/*   TRANSACTION TYPE = SQ1  */

typedef struct query_paynote_info
{
   transaction_type_t transaction_type;
   series_t series;
   int32_t pay_note_number_i;
   uint16_t segment_number_n;
   char filler_2_s [2];
   char date_s [8];
} query_paynote_info_t;


/*   TRANSACTION TYPE = CQ3  */

typedef struct query_position
{
   transaction_type_t transaction_type;
   series_t series;
   search_series_t search_series;
   account_t account;
   uint16_t segment_number_n;
   char date_s [8];
   char filler_2_s [2];
} query_position_t;


/*   TRANSACTION TYPE = CQ122  */

typedef struct query_position_history
{
   transaction_type_t transaction_type;
   series_t series;
   account_t account;
   char date_s [8];
} query_position_history_t;


/*   TRANSACTION TYPE = CQ65  */

typedef struct query_pos_level
{
   transaction_type_t transaction_type;
   series_t series;
   account_t account;
   char series_id_s [32];
   int32_t summary_i;
   uint16_t segment_number_n;
   char filler_2_s [2];
   char date_s [8];
   char account_type_s [12];
   int32_t level_type_i;
} query_pos_level_t;


/*   TRANSACTION TYPE = II17  */

typedef struct query_prel_settlement
{
   transaction_type_t transaction_type;
   series_t series;
   char settlement_date_s [8];
   uint16_t segment_number_n;
   uint8_t settlement_price_type_c;
   char filler_1_s;
} query_prel_settlement_t;


/*   TRANSACTION TYPE = DQ90  */

typedef struct query_pre_trade_limit
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_pre_trade_limit_t;


/*   TRANSACTION TYPE = ML58  */

typedef struct query_price_limit_trigger
{
   transaction_type_t transaction_type;
   series_t series;
   uint8_t only_this_series_c;
   char filler_3_s [3];
} query_price_limit_trigger_t;


/*   TRANSACTION TYPE = RQ44  */

typedef struct query_realtime_ulg_price
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char date_s [8];
   char filler_2_s [2];
} query_realtime_ulg_price_t;


/*   TRANSACTION TYPE = CQ16  */

typedef struct query_rectify_d
{
   transaction_type_t transaction_type;
   series_t series;
   search_series_t search_series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_rectify_d_t;


/*   TRANSACTION TYPE = CQ17  */

typedef struct query_rectify_d_cont
{
   transaction_type_t transaction_type;
   series_t series;
   int64_t rectify_deal_number_q;
} query_rectify_d_cont_t;


/*   TRANSACTION TYPE = CQ14  */

typedef struct query_rectify_t
{
   transaction_type_t transaction_type;
   series_t series;
   uint8_t instance_c;
   char filler_1_s;
   uint16_t segment_number_n;
   search_series_t search_series;
} query_rectify_t_t;


/*   TRANSACTION TYPE = CQ15  */

typedef struct query_rectify_t_cont
{
   transaction_type_t transaction_type;
   series_t series;
   int32_t rectify_trade_number_i;
} query_rectify_t_cont_t;


/*   TRANSACTION TYPE = LR6  */

typedef struct query_report_nrs
{
   transaction_type_t transaction_type;
   int32_t report_no_i;
   uint16_t segment_number_n;
   char country_id_s [2];
   char ex_customer_s [5];
   char report_spec_s [5];
   char clh_id_s [12];
   char business_date_s [8];
   uint8_t only_account_reports_c;
   char filler_1_s;
} query_report_nrs_t;


/*   TRANSACTION TYPE = LQ4  */

typedef struct query_report_ver
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char date_s [8];
   char filler_2_s [2];
   int32_t info_type_i;
} query_report_ver_t;


/*   TRANSACTION TYPE = JQ21  */

typedef struct query_risk_margin_scaling_factor
{
   transaction_type_t transaction_type;
   series_t series;
   account_t account;
   int32_t sequence_number_n;
   uint16_t segment_number_n;
   uint8_t run_type_c;
   char business_date_s [8];
   char filler_1_s;
} query_risk_margin_scaling_factor_t;


/*   TRANSACTION TYPE = JQ277  */

typedef struct query_risk_margin_scaling_factor_internal
{
   transaction_type_t transaction_type;
   series_t series;
   account_t account;
   char clh_id_s [12];
   int32_t sequence_number_n;
   uint16_t segment_number_n;
   uint8_t run_type_c;
   char business_date_s [8];
   char filler_1_s;
} query_risk_margin_scaling_factor_internal_t;


/*   TRANSACTION TYPE = JQ71  */

typedef struct query_rm_margin_sim
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   uint16_t qry_segment_number_n;
   uint8_t last_qry_segment_c;
   char filler_3_s [3];
   uint16_t items_n;
   uint16_t size_n;
} query_rm_margin_sim_t;


/*   TRANSACTION TYPE = JQ10  */

typedef struct query_rm_param_obj
{
   transaction_type_t transaction_type;
   series_t series;
   char series_id_s [32];
   char business_date_s [8];
   int32_t sequence_number_n;
   uint16_t segment_number_n;
   char clh_id_s [12];
   char margin_class_s [3];
   uint8_t run_type_c;
   uint8_t margin_class_filter_c;
   char filler_1_s;
} query_rm_param_obj_t;


/*   TRANSACTION TYPE = FQ40  */

typedef struct query_segment_hdr
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   uint16_t items_n;
   uint16_t size_n;
   char filler_2_s [2];
} query_segment_hdr_t;


/*   TRANSACTION TYPE = DQ2, DQ9  */

typedef struct query_series
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_series_t;


/*   TRANSACTION TYPE = FQ29  */

typedef struct query_settlement_instruction
{
   transaction_type_t transaction_type;
   series_t series;
   account_t account;
   char bank_id_s [12];
   char currency_s [3];
   char int_id_s [8];
   uint8_t ssi_type_c;
   int64_t ssi_id_q;
   uint8_t tax_code_c;
   uint8_t clh_account_info_only_c;
   char clh_account_id_s [32];
   uint16_t segment_number_n;
   uint16_t items_n;
   char filler_2_s [2];
   query_settlement_instruction_item_t item [20];
} query_settlement_instruction_t;


/*   TRANSACTION TYPE = CQ31  */

typedef struct query_simulate_fee
{
   transaction_type_t transaction_type;
   series_t series;
   int32_t deal_price_i;
   int64_t deal_quantity_i;
   account_t account;
   uint8_t bid_or_ask_c;
   uint8_t open_close_req_c;
   char filler_2_s [2];
} query_simulate_fee_t;


/*   TRANSACTION TYPE = DQ76  */

typedef struct query_state_type
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_state_type_t;


/*   TRANSACTION TYPE = IQ12  */

typedef struct query_tot_equil_prices
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_tot_equil_prices_t;


/*   TRANSACTION TYPE = MQ7  */

typedef struct query_tot_ob
{
   transaction_type_t transaction_type;
   series_t series;
   quad_word order_number_u;
   uint8_t bid_or_ask_c;
   uint8_t only_this_series_c;
   char filler_2_s [2];
} query_tot_ob_t;


/*   TRANSACTION TYPE = MQ5, MQ78  */

typedef struct query_tot_order
{
   transaction_type_t transaction_type;
   series_t series;
   whose_t whose;
   uint16_t stp_key_i;
   char filler_2_s [2];
   uint32_t order_index_u;
} query_tot_order_t;


/*   TRANSACTION TYPE = MQ80  */

typedef struct query_tot_party
{
   transaction_type_t transaction_type;
   series_t series;
   quad_word order_number_u;
   uint8_t bid_or_ask_c;
   char filler_3_s [3];
} query_tot_party_t;


/*   TRANSACTION TYPE = KQ1  */

typedef struct query_trade_report_otc
{
   transaction_type_t transaction_type;
   series_t series;
   party_t party;
   account_t account;
   uint16_t segment_number_n;
   char filler_2_s [2];
   char from_date_s [8];
   char to_date_s [8];
   char passthrough_s [32];
   char series_id_s [32];
   uint32_t trade_report_type_i;
   uint8_t trade_report_state_c;
   uint8_t bought_or_sold_c;
   uint8_t date_span_type_c;
   char filler_1_s;
} query_trade_report_otc_t;


/*   TRANSACTION TYPE = DQ45  */

typedef struct query_trade_report_types
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_trade_report_types_t;


/*   TRANSACTION TYPE = IQ42  */

typedef struct query_trade_statistics
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char date_s [8];
   char filler_2_s [2];
} query_trade_statistics_t;


/*   TRANSACTION TYPE = TR70  */

typedef struct query_trade_ticker
{
   transaction_type_t transaction_type;
   series_t series;
   series_t search_series;
   time_spec_t timestamp;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_trade_ticker_t;


/*   TRANSACTION TYPE = DQ29  */

typedef struct query_trading_state
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_trading_state_t;


/*   TRANSACTION TYPE = DQ19, DQ4  */

typedef struct query_underlying
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_underlying_t;


/*   TRANSACTION TYPE = DQ14  */

typedef struct query_underlying_adjustment
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char date_adjust_s [8];
   char filler_2_s [2];
} query_underlying_adjustment_t;


/*   TRANSACTION TYPE = CQ40  */

typedef struct query_updated_pos_info
{
   transaction_type_t transaction_type;
   series_t series;
   search_series_t search_series;
   account_t account;
   uint16_t segment_number_n;
   char modified_date_s [8];
   char modified_time_s [6];
} query_updated_pos_info_t;


/*   TRANSACTION TYPE = JQ11  */

typedef struct query_used_marg_params
{
   transaction_type_t transaction_type;
   series_t series;
   int32_t sequence_number_n;
   uint16_t segment_number_n;
   char business_date_s [8];
   char clh_id_s [12];
   char margin_class_s [3];
   uint8_t run_type_c;
   uint8_t margin_class_filter_c;
   char filler_1_s;
} query_used_marg_params_t;


/*   TRANSACTION TYPE = DQ30  */

typedef struct query_user_type_info
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_user_type_info_t;


/*   TRANSACTION TYPE = DQ132  */

typedef struct query_valuation_group
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   char filler_2_s [2];
} query_valuation_group_t;


/*   TRANSACTION TYPE = BO25, BO5, MA476, MA92  */
/*   NAMED STRUCT = 34949  */

typedef struct ranking_time
{
   time_spec_t timestamp_ranking;
} ranking_time_t;


/*   TRANSACTION TYPE = CD31  */

typedef struct rectify_deal
{
   transaction_type_t transaction_type;
   series_t series;
   uint8_t instance_c;
   uint8_t operation_c;
   uint16_t items_n;
   other_series_t other_series;
   int32_t deal_price_i;
   int32_t deal_number_i;
   rectify_deal_item_t item [255];
} rectify_deal_t;


/*   TRANSACTION TYPE = KC1  */

typedef struct rectify_otc_trade_report
{
   transaction_type_t transaction_type;
   series_t series;
   uint64_t trade_report_nbr_q;
   uint16_t items_n;
   uint16_t size_n;
} rectify_otc_trade_report_t;


/*   TRANSACTION TYPE = CD28  */

typedef struct rectify_trade
{
   transaction_type_t transaction_type;
   series_t series;
   int32_t trade_number_i;
   uint8_t items_c;
   char filler_3_s [3];
   rectify_trade_item_t item [100];
} rectify_trade_t;


/*   TRANSACTION TYPE = CC42  */

typedef struct register_account
{
   transaction_type_t transaction_type;
   series_t series;
   account_t account;
   store_account_t store_account;
} register_account_t;


/*   TRANSACTION TYPE = CC40  */

typedef struct reject_give_up_request
{
   transaction_type_t transaction_type;
   series_t series;
   int32_t give_up_number_i;
   char give_up_text_s [30];
   char filler_2_s [2];
} reject_give_up_request_t;


/*   TRANSACTION TYPE = JC9  */

typedef struct report_marginable_spread_rm
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t segment_number_n;
   uint16_t items_n;
} report_marginable_spread_rm_t;


/*   BROADCAST TYPE = BI93  */

typedef struct report_ready
{
   broadcast_type_t broadcast_type;
   int32_t report_no_i;
   char country_id_s [2];
   char clh_id_s [12];
   char report_spec_s [5];
   char business_date_s [8];
   char as_of_date_s [8];
   char sent_date_s [8];
   char sent_time_s [6];
   char filler_3_s [3];
} report_ready_t;


/*   TRANSACTION TYPE = BO25, BO5, MA476, MA92, MO1, MO3, MO385, MO387  */
/*   NAMED STRUCT = 34812  */

typedef struct reserve_order
{
   int64_t display_quantity_i;
   int64_t original_display_quantity_i;
} reserve_order_t;


/*   TRANSACTION TYPE = CD55  */

typedef struct restore_position
{
   transaction_type_t transaction_type;
   series_t series;
   account_t account;
   int64_t closeout_qty_i;
   char date_s [8];
} restore_position_t;


/*   TRANSACTION TYPE = CB146, KB10  */
/*   NAMED STRUCT = 50010  */

typedef struct risk_exposure_limit_vim
{
   account_t mra_account;
   uint64_t trade_report_nbr_q;
   int64_t margin_requirement_q;
   int64_t margin_requirement_without_trade_q;
   int64_t exposure_limit_q;
   char currency_s [3];
   char filler_1_s;
} risk_exposure_limit_vim_t;


/*   TRANSACTION TYPE = JA21, JA277  */
/*   NAMED STRUCT = 21043  */

typedef struct risk_scale
{
   account_t account;
   int16_t risk_margin_scaling_factor_n;
   char country_id_s [2];
   char mar_id_s [5];
   char filler_3_s [3];
} risk_scale_t;


/*   TRANSACTION TYPE = JQ71  */
/*   NAMED STRUCT = 21044  */

typedef struct rm_margin_simulation
{
   series_t series;
   account_t account;
   uint8_t pos_sim_c;
   uint8_t price_sim_c;
   uint8_t vol_sim_c;
   uint8_t output_level_c;
   char filler_1_s;
   char date_s [8];
   uint8_t series_exp_today_sim_c;
   uint8_t fut_pl_sim_c;
   char sub_user_s [32];
   char margin_class_s [3];
   char filler_2_s [2];
} rm_margin_simulation_t;


/*   TRANSACTION TYPE = JA71  */
/*   NAMED STRUCT = 21053  */

typedef struct rm_margin_sim_del
{
   series_t series;
   int64_t market_margin_q;
   char market_currency_s [3];
   char filler_1_s;
   int64_t nbr_held_q;
   int64_t nbr_written_q;
   int64_t market_value_q;
   int64_t price_spread_margin_q;
   int64_t naked_margin_q;
} rm_margin_sim_del_t;


/*   TRANSACTION TYPE = JA71  */
/*   NAMED STRUCT = 21050  */

typedef struct rm_margin_sim_failure_reason
{
   char failure_reason_s [160];
} rm_margin_sim_failure_reason_t;


/*   TRANSACTION TYPE = JQ71  */
/*   NAMED STRUCT = 21045  */

typedef struct rm_margin_sim_markets
{
   series_t series;
} rm_margin_sim_markets_t;


/*   TRANSACTION TYPE = JA71  */
/*   NAMED STRUCT = 21048  */

typedef struct rm_margin_sim_oms2_ivl
{
   series_t series;
   int32_t val_ivl_mid_i;
   int32_t val_ivl_low_i;
   int32_t val_ivl_high_i;
   uint16_t dec_in_ivl_n;
   char filler_2_s [2];
} rm_margin_sim_oms2_ivl_t;


/*   TRANSACTION TYPE = JA71  */
/*   NAMED STRUCT = 21055  */

typedef struct rm_margin_sim_pay
{
   series_t series;
   int64_t market_margin_q;
   char market_currency_s [3];
   char filler_1_s;
   int64_t naked_margin_q;
} rm_margin_sim_pay_t;


/*   TRANSACTION TYPE = JA71  */
/*   NAMED STRUCT = 21051  */

typedef struct rm_margin_sim_pos
{
   int64_t market_margin_q;
   char currency_s [3];
   char filler_1_s;
   int64_t nbr_held_q;
   int64_t nbr_written_q;
   int64_t market_value_q;
   int64_t price_spread_margin_q;
   int64_t naked_margin_q;
   series_t series;
   account_t account;
} rm_margin_sim_pos_t;


/*   TRANSACTION TYPE = JA71  */
/*   NAMED STRUCT = 21047  */

typedef struct rm_margin_sim_prices
{
   series_t series;
   uint32_t bid_price_i;
   uint32_t ask_price_i;
   int32_t marg_price_i;
   int32_t fixing_value_i;
   int64_t margin_one_long_q;
   int64_t margin_one_short_q;
   uint16_t dec_in_price_n;
   char filler_2_s [2];
} rm_margin_sim_prices_t;


/*   TRANSACTION TYPE = JQ71  */
/*   NAMED STRUCT = 21088  */

typedef struct rm_margin_sim_repo_trades
{
   account_t pos_account;
   series_t series;
   int64_t sim_qty_q;
   int32_t clean_price_i;
   int32_t repo_rate_i;
   uint8_t item_type_c;
   char filler_3_s [3];
} rm_margin_sim_repo_trades_t;


/*   TRANSACTION TYPE = JA71  */
/*   NAMED STRUCT = 21101  */

typedef struct rm_margin_sim_settl
{
   series_t series;
   int64_t market_margin_q;
   char market_currency_s [3];
   char filler_1_s;
   int64_t nbr_held_q;
   int64_t nbr_written_q;
   int64_t market_value_q;
   int64_t price_spread_margin_q;
   int64_t naked_margin_q;
} rm_margin_sim_settl_t;


/*   TRANSACTION TYPE = JA71  */
/*   NAMED STRUCT = 21052  */

typedef struct rm_margin_sim_sum
{
   series_t series;
   int64_t market_margin_q;
   int64_t risk_margin_q;
   char market_currency_s [3];
   char risk_currency_s [3];
   char filler_2_s [2];
} rm_margin_sim_sum_t;


/*   TRANSACTION TYPE = JA71  */
/*   NAMED STRUCT = 21056  */

typedef struct rm_margin_sim_sum_pay_ulg
{
   series_t series;
   int64_t market_margin_q;
   char market_currency_s [3];
   char filler_1_s;
} rm_margin_sim_sum_pay_ulg_t;


/*   TRANSACTION TYPE = JA71  */
/*   NAMED STRUCT = 21054  */

typedef struct rm_margin_sim_sum_pos_ulg
{
   series_t series;
   int64_t market_margin_q;
   char market_currency_s [3];
   char filler_1_s;
   int64_t naked_margin_q;
   int32_t marg_price_i;
   uint16_t dec_in_price_n;
   char filler_2_s [2];
} rm_margin_sim_sum_pos_ulg_t;


/*   TRANSACTION TYPE = JQ71  */
/*   NAMED STRUCT = 21046  */

typedef struct rm_margin_sim_trades
{
   uint8_t item_type_c;
   char filler_3_s [3];
   series_t series;
   int64_t sim_qty_q;
   int32_t trade_price_sim_i;
   int32_t reserved_i;
   char closing_date_s [8];
   char date_settlement_s [8];
   char reserved_8_s [8];
} rm_margin_sim_trades_t;


/*   TRANSACTION TYPE = JQ71  */
/*   NAMED STRUCT = 21072  */

typedef struct rm_margin_sim_trades_account
{
   account_t account;
} rm_margin_sim_trades_account_t;


/*   TRANSACTION TYPE = JA71  */
/*   NAMED STRUCT = 21049  */

typedef struct rm_margin_sim_vola
{
   series_t series;
   int32_t vol_ivl_long_mid_i;
   int32_t vol_ivl_short_mid_i;
   int32_t vol_ivl_long_low_i;
   int32_t vol_ivl_short_low_i;
   int32_t vol_ivl_long_high_i;
   int32_t vol_ivl_short_high_i;
   int64_t margin_one_short_q;
} rm_margin_sim_vola_t;


/*   TRANSACTION TYPE = BI84  */
/*   NAMED STRUCT = 71  */

typedef struct rpt_service
{
   uint8_t report_system_event_c;
   char service_description_s [255];
   uint8_t subsystem_c;
} rpt_service_t;


/*   TRANSACTION TYPE = FA14, FA15, FA16, FA19  */
/*   NAMED STRUCT = 18037  */

typedef struct run_info
{
   uint32_t request_nbr_u;
   uint32_t margin_sequence_nbr_u;
   char valuation_date_s [8];
   char created_date_s [8];
   char created_time_s [6];
   char margin_date_s [8];
   char margin_time_s [6];
   char clh_id_s [12];
   uint8_t collateral_evaluation_type_c;
   uint8_t create_direct_debit_c;
   uint8_t intraday_evaluation_c;
   char filler_1_s;
} run_info_t;


/*   TRANSACTION TYPE = FA1, FA2, FB1  */
/*   NAMED STRUCT = 18009  */

typedef struct security
{
   collateral_base_t collateral_base;
   uint8_t security_type_c;
   char filler_3_s [3];
} security_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34901  */

typedef struct segment_instance_number
{
   uint16_t segment_number_n;
   uint8_t instance_c;
   char filler_1_s;
   uint32_t sequence_number_u;
   trading_code_t trading_code;
} segment_instance_number_t;


/*   TRANSACTION TYPE = FA22, FB6, KB14  */
/*   NAMED STRUCT = 18023  */

typedef struct sequence_number_info
{
   int32_t sequence_number_n;
} sequence_number_info_t;


/*   TRANSACTION TYPE = FA22, FB6  */
/*   NAMED STRUCT = 18060  */

typedef struct sequence_number_info_int
{
   char created_clearing_date_s [8];
   char modified_clearing_date_s [8];
} sequence_number_info_int_t;


/*   BROADCAST TYPE = BU1009  */

typedef struct series_bo_multi_update_bu1009
{
   broadcast_type_t broadcast_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   series_bo_multi_update_bu1009_item_t item [7];
} series_bo_multi_update_bu1009_t;


/*   BROADCAST TYPE = BU9  */

typedef struct series_bo_update_bu9
{
   broadcast_type_t broadcast_type;
   uint16_t chg_type_n;
   char filler_2_s [2];
   da9_t da9;
} series_bo_update_bu9_t;


/*   BROADCAST TYPE = BU1002  */

typedef struct series_multi_update_bu1002
{
   broadcast_type_t broadcast_type;
   uint16_t segment_number_n;
   uint16_t items_n;
   series_multi_update_bu1002_item_t item [6];
} series_multi_update_bu1002_t;


/*   BROADCAST TYPE = BU2  */

typedef struct series_update_bu2
{
   broadcast_type_t broadcast_type;
   uint16_t chg_type_n;
   char filler_2_s [2];
   da2_t da2;
} series_update_bu2_t;


/*   TRANSACTION TYPE = FA20, FA21, FA22, FA24, FB6  */
/*   NAMED STRUCT = 18069  */

typedef struct settlement_instruction_info
{
   char account_number_s [34];
   char account_name_s [50];
   char bic_code_s [15];
   char aba_number_s [34];
   char clh_bank_account_number_s [34];
   char clh_bank_account_name_s [50];
   char clh_bank_bic_code_s [15];
   char intermediary_bic_code_s [15];
   char intermediary_bank_name_s [50];
   char bank_id_s [12];
   char clh_bank_id_s [12];
   char filler_3_s [3];
} settlement_instruction_info_t;


/*   BROADCAST TYPE = BI63  */

typedef struct settle_price_update
{
   broadcast_type_t broadcast_type;
   uint16_t items_n;
   char filler_2_s [2];
   settle_price_update_item_t item [30];
} settle_price_update_t;


/*   TRANSACTION TYPE = ML2152, ML2155  */

typedef struct set_delta_limit_trans
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t items_n;
   char filler_2_s [2];
   set_delta_limit_trans_item_t item [100];
} set_delta_limit_trans_t;


/*   TRANSACTION TYPE = CC14  */

typedef struct set_deny_exercise
{
   transaction_type_t transaction_type;
   series_t series;
   account_t account;
   int64_t deny_exercise_q;
} set_deny_exercise_t;


/*   TRANSACTION TYPE = DC87  */

typedef struct set_mm_protection
{
   transaction_type_t transaction_type;
   series_t series;
   da87_t da87;
} set_mm_protection_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34808  */

typedef struct single_order_insert
{
   transaction_type_t transaction_type;
   series_t series;
   uint16_t items_n;
   uint16_t size_n;
} single_order_insert_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34809  */

typedef struct single_order_update
{
   transaction_type_t transaction_type;
   series_t series;
   quad_word order_number_u;
   uint8_t bid_or_ask_c;
   char filler_3_s [3];
   uint16_t items_n;
   uint16_t size_n;
} single_order_update_t;


/*   TRANSACTION TYPE = JA10  */
/*   NAMED STRUCT = 21017  */

typedef struct srs_cfm_param
{
   char cfm_id_s [16];
   int32_t vol_int_down_i;
   int32_t vol_int_up_i;
} srs_cfm_param_t;


/*   TRANSACTION TYPE = JA10  */
/*   NAMED STRUCT = 21147  */

typedef struct srs_dh_param
{
   int64_t down_int_scan_q;
   int64_t up_int_scan_q;
   int64_t deliv_charge_spreads_rm_q;
   int64_t deliv_charge_outrights_rm_q;
   int32_t vol_down_rm_i;
   int32_t vol_up_rm_i;
   int32_t delta_scale_fac_rm_i;
   int16_t down_int_3t_rm_n;
   int16_t up_int_3t_rm_n;
   char dhg_id_s [16];
   char cco_id_s [6];
   char filler_2_s [2];
} srs_dh_param_t;


/*   TRANSACTION TYPE = JA10  */
/*   NAMED STRUCT = 21019  */

typedef struct srs_marg_param
{
   series_t series;
   char margin_class_s [3];
   uint8_t marg_meth_inst_c;
} srs_marg_param_t;


/*   TRANSACTION TYPE = JA10  */
/*   NAMED STRUCT = 21018  */

typedef struct srs_oms2_param
{
   char oms_id_s [16];
   char window_class_id_s [16];
   int32_t val_int_down_i;
   int32_t val_int_up_i;
   int32_t vol_int_down_i;
   int32_t vol_int_up_i;
} srs_oms2_param_t;


/*   TRANSACTION TYPE = JA10  */
/*   NAMED STRUCT = 21016  */

typedef struct srs_pri_param
{
   char ppr_id_s [16];
   int32_t dividend_yield_i;
   int32_t risk_free_rate_i;
   int32_t fixed_vol_rm_i;
} srs_pri_param_t;


/*   TRANSACTION TYPE = FA29  */
/*   NAMED STRUCT = 18071  */

typedef struct standard_settlement_instruction_details
{
   account_t account;
   trading_code_t trading_code;
   uint16_t version_n;
   uint8_t ssi_type_c;
   uint8_t state_c;
   int64_t ssi_id_q;
   char bank_id_s [12];
   char int_id_s [8];
   char bank_name_s [50];
   char bic_code_s [15];
   char account_number_s [34];
   char account_name_s [50];
   char currency_s [3];
   char clh_account_id_s [32];
   char aba_number_s [34];
   uint8_t tax_code_c;
   char created_date_s [8];
   char created_time_s [6];
   char filler_3_s [3];
} standard_settlement_instruction_details_t;


/*   TRANSACTION TYPE = KA1, KB1, KC1  */
/*   NAMED STRUCT = 38009  */

typedef struct standard_trade_report
{
   int64_t quantity_i;
   int32_t premium_i;
   char filler_8_s [8];
   char customer_info_s [15];
   uint8_t open_close_req_c;
   uint8_t ext_t_state_c;
   char exchange_info_s [32];
   char time_of_agreement_date_s [8];
   char time_of_agreement_time_s [6];
   char filler_1_s;
   match_id_t match_id;
   quad_word order_number_u;
} standard_trade_report_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34017  */

typedef struct stop_order_trans
{
   transaction_type_t transaction_type;
   series_t series;
   order_var_t order_var;
   stop_series_t stop_series;
   int32_t limit_premium_i;
   give_up_member_t give_up_member;
   char exchange_info_s [32];
   int64_t total_volume_i;
} stop_order_trans_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34117  */

typedef struct stop_order_trans_p
{
   transaction_type_t transaction_type;
   series_t series;
   trading_code_t trading_code;
   order_var_t order_var;
   stop_series_t stop_series;
   int32_t limit_premium_i;
   give_up_member_t give_up_member;
   char exchange_info_s [32];
   int64_t total_volume_i;
} stop_order_trans_p_t;


/*   TRANSACTION TYPE = BD2, BD6, BD70, BD71, BI81, BI84, BO16, BO17, BO25, BO5, BO55, BU120, BU121, BU122, BU123, BU124, BU125, BU126, BU134, BU136, BU90, CA10, CA11, CA117, CA128, CA129, CA132, CB146, CB31, CC91, CC92, DA120, DA121, DA122, DA123, DA124, DA125, DA126, DA130, DA131, DA134, DA136, DA90, DC90, FA1, FA14, FA15, FA16, FA17, FA19, FA2, FA20, FA21, FA22, FA24, FA29, FA40, FB1, FB17, FB18, FB6, FQ40, IA21, IA22, IQ21, IQ22, JA1, JA10, JA11, JA21, JA277, JA31, JA54, JA55, JA7, JA71, JA9, JB1, JB2, JC9, JQ71, KA1, KB1, KB10, KB14, KC1, MA476, MA92, MO1, MO3, MO385, MO387, TA70, TA71, UA14  */

typedef struct sub_item_hdr
{
   uint16_t named_struct_n;
   uint16_t size_n;
} sub_item_hdr_t;


/*   BROADCAST TYPE = BI1  */

typedef struct suspend_resume_trading
{
   broadcast_type_t broadcast_type;
   uint16_t commodity_n;
   uint8_t on_off_c;
   char filler_1_s;
} suspend_resume_trading_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34807  */

typedef struct time_in_force
{
   uint16_t time_validity_n;
   char filler_2_s [2];
} time_in_force_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34014  */

typedef struct tm_trade_rpt_trans
{
   transaction_type_t transaction_type;
   series_t series;
   order_var_t order_var;
   party_t party;
   uint16_t commodity_n;
   uint16_t expiration_date_n;
   int32_t strike_price_i;
   char exchange_info_s [32];
} tm_trade_rpt_trans_t;


/*   TRANSACTION TYPE = BO25, BO5, MO75  */
/*   NAMED STRUCT = 34021  */

typedef struct trade_report_1_trans
{
   transaction_type_t transaction_type;
   series_t series;
   order_var_t order_var;
   party_t party;
   char exchange_info_s [32];
   give_up_member_t give_up_member;
   char settlement_date_s [8];
   char time_of_agreement_date_s [8];
   char time_of_agreement_time_s [6];
   uint8_t deferred_publication_c;
   char filler_1_s;
} trade_report_1_trans_t;


/*   TRANSACTION TYPE = BO25, BO5, MO459  */
/*   NAMED STRUCT = 34119  */

typedef struct trade_report_1_trans_p
{
   transaction_type_t transaction_type;
   series_t series;
   trading_code_t trading_code;
   order_var_t order_var;
   party_t party;
   char exchange_info_s [32];
   give_up_member_t give_up_member;
   char settlement_date_s [8];
   char time_of_agreement_date_s [8];
   char time_of_agreement_time_s [6];
   uint8_t deferred_publication_c;
   char filler_1_s;
} trade_report_1_trans_p_t;


/*   TRANSACTION TYPE = BO25, BO5, MO76  */
/*   NAMED STRUCT = 34022  */

typedef struct trade_report_2_trans
{
   transaction_type_t transaction_type;
   series_t series;
   int64_t mp_quantity_i;
   int32_t premium_i;
   uint32_t block_n;
   char settlement_date_s [8];
   char time_of_agreement_date_s [8];
   char time_of_agreement_time_s [6];
   uint8_t ext_t_state_c;
   uint8_t deferred_publication_c;
   trd_rpt_cust_t bid_side;
   trd_rpt_cust_t ask_side;
} trade_report_2_trans_t;


/*   TRANSACTION TYPE = BO55  */
/*   NAMED STRUCT = 34836  */

typedef struct trade_report_base
{
   series_t series;
   party_t party;
   quad_word order_number_u;
   int32_t premium_i;
   int64_t quantity_i;
   uint8_t bid_or_ask_c;
   uint8_t trade_report_type;
   char time_of_agreement_date_s [8];
   char time_of_agreement_time_s [6];
   char settlement_date_s [8];
   uint8_t deferred_publication_c;
   uint8_t ob_command_c;
   char filler_2_s [2];
} trade_report_base_t;


/*   TRANSACTION TYPE = BD70, TA70  */
/*   NAMED STRUCT = 34403  */

typedef struct trade_report_trade_ticker
{
   uint8_t trade_report_type;
   char settlement_date_s [8];
   char time_of_agreement_date_s [8];
   char time_of_agreement_time_s [6];
   uint8_t outside_info_spread_c;
} trade_report_trade_ticker_t;


/*   TRANSACTION TYPE = BO25, BO5  */
/*   NAMED STRUCT = 34018  */

typedef struct trade_report_trans
{
   transaction_type_t transaction_type;
   series_t series;
   int64_t mp_quantity_i;
   int32_t premium_i;
   uint32_t block_n;
   uint8_t ext_t_state_c;
   char filler_3_s [3];
   bid_side_t bid_side;
   ask_side_t ask_side;
} trade_report_trans_t;


/*   TRANSACTION TYPE = BD71, TA71  */
/*   NAMED STRUCT = 34406  */

typedef struct trade_ticker_amend
{
   uint64_t execution_event_nbr_u;
   uint32_t match_group_nbr_u;
   uint8_t trade_state_c;
   char include_in_statistics_c;
   char filler_2_s [2];
} trade_ticker_amend_t;


/*   TRANSACTION TYPE = DC90  */

typedef struct trans_segment_hdr
{
   transaction_type_t transaction_type;
   uint16_t items_n;
   uint16_t size_n;
   uint16_t segment_number_n;
   char filler_2_s [2];
} trans_segment_hdr_t;


/*   TRANSACTION TYPE = BO25, BO5, MA476, MA92, MO1, MO385  */
/*   NAMED STRUCT = 34838  */

typedef struct trigger_on_session_order
{
   int16_t session_type_id_n;
   uint16_t time_validity_n;
} trigger_on_session_order_t;


/*   TRANSACTION TYPE = BO25, BO5, MA476, MA92, MO1, MO385  */
/*   NAMED STRUCT = 34811  */

typedef struct trigger_order
{
   stop_series_t stop_series;
   int32_t limit_premium_i;
   uint16_t time_validity_n;
   uint8_t stop_condition_c;
   char filler_1_s;
} trigger_order_t;


/*   BROADCAST TYPE = BU19, BU4  */

typedef struct underlying_update_bu4_bu19
{
   broadcast_type_t broadcast_type;
   uint16_t chg_type_n;
   char filler_2_s [2];
   da4_da19_t da4_da19;
} underlying_update_bu4_bu19_t;


/*   BROADCAST TYPE = BI73  */

typedef struct undo_info_ready
{
   broadcast_type_t broadcast_type;
   int32_t info_type_i;
   series_t series;
   char business_date_s [8];
   char clearing_date_s [8];
   char sent_date_s [8];
   char sent_time_s [6];
   uint16_t seq_num_srm_n;
} undo_info_ready_t;


/*   TRANSACTION TYPE = JA11  */
/*   NAMED STRUCT = 21149  */

typedef struct used_comb_com_group_params
{
   char ccg_id_s [3];
   char filler_1_s;
   int32_t credit_rate_rm_i;
   int16_t tier_1_rm_n;
   int16_t tier_2_rm_n;
   int16_t tier_3_rm_n;
   int16_t tier_4_rm_n;
   uint16_t priority_n;
   char filler_2_s [2];
   char cco_id_1_s [6];
   char cco_id_2_s [6];
   char cco_id_3_s [6];
   char cco_id_4_s [6];
   int8_t ds_ratio_1_rm_c;
   int8_t ds_ratio_2_rm_c;
   int8_t ds_ratio_3_rm_c;
   int8_t ds_ratio_4_rm_c;
   uint8_t a_or_b_1_rm_c;
   uint8_t a_or_b_2_rm_c;
   uint8_t a_or_b_3_rm_c;
   uint8_t a_or_b_4_rm_c;
} used_comb_com_group_params_t;


/*   TRANSACTION TYPE = JA11  */
/*   NAMED STRUCT = 21112  */

typedef struct used_comb_com_params
{
   int32_t short_opt_min_charge_i;
   int32_t init_to_maint_speculator_rm_i;
   int32_t init_to_maint_omnibus_rm_i;
   int32_t init_to_maint_hedge_rm_i;
   char cco_id_s [6];
   char tie_id_s [12];
   char irm_id_s [12];
   char ccg_id_s [3];
   char ic_tie_id_s [12];
   int8_t risk_expo_rm_c;
   uint8_t limit_opt_rm_c;
   uint8_t written_opt_rm_c;
   uint8_t exp_month_in_rpf_rm_c;
   uint8_t granularity_c;
   char filler_6_s [6];
} used_comb_com_params_t;


/*   TRANSACTION TYPE = JA11  */
/*   NAMED STRUCT = 21111  */

typedef struct used_delta_hedge_params
{
   char dhg_id_s [16];
   int32_t extr_move_cov_rm_i;
   int32_t offset_days_zero_risk_rm_i;
   int32_t erosion_rm_i;
   int32_t er_trd_days_in_year_rm_i;
   int16_t offset_days_intr_rm_n;
   int16_t offset_days_end_rm_n;
   uint8_t val_interv_base_scan_c;
   int8_t dec_in_risk_array_c;
   uint8_t cap_neg_scenario_price_c;
   uint8_t zero_risk_till_exp_date_rm_c;
   uint8_t incl_opt_prem_rm_c;
   uint8_t backtest_phys_del_rm_c;
   uint8_t base_for_adjustment_c;
   uint8_t deliv_margin_rm_c;
   uint8_t paym_margin_rm_c;
   uint8_t base_offset_days_rm_c;
   uint8_t val_interv_type_scan_c;
   uint8_t vol_interv_type_rm_c;
   uint8_t time_dep_base_dhg_c;
   uint8_t incl_in_seq_nbr_change_c;
   uint8_t reference_date_dhg_c;
   uint8_t reference_time_of_day_c;
   uint8_t interpolation_rm_c;
   char filler_3_s [3];
} used_delta_hedge_params_t;


/*   TRANSACTION TYPE = JA11  */
/*   NAMED STRUCT = 21151  */

typedef struct used_global_risk_marg_class
{
   char pgr_id_s [12];
   char mrg_id_s [3];
} used_global_risk_marg_class_t;


/*   TRANSACTION TYPE = JA11  */
/*   NAMED STRUCT = 21150  */

typedef struct used_global_risk_params
{
   char pgr_id_s [12];
   char default_currency_s [3];
   char exchange_complex_s [6];
   char risk_file_exchange_acronym_s [3];
   char risk_file_exchange_code_s [2];
   uint8_t gross_marg_meth_intra_c;
   char filler_1_s;
   int32_t iter_max_no_i;
   int64_t iter_accuracy_q;
   uint16_t margin_offset_limit_n;
   uint16_t dec_in_accuracy_n;
   uint16_t time_steps_n;
   uint16_t dec_in_delta_weight_n;
   uint8_t incl_expiring_series_c;
   uint8_t create_riskparam_file_c;
   uint8_t decimal_composit_delta_c;
   uint8_t gross_marg_meth_c;
   uint32_t delta_weight_1_i;
   uint32_t delta_weight_2_i;
   uint32_t delta_weight_3_i;
   uint32_t delta_weight_4_i;
   uint32_t delta_weight_5_i;
   uint32_t delta_weight_6_i;
   uint32_t delta_weight_7_i;
   uint32_t delta_weight_8_i;
   uint32_t delta_weight_9_i;
   uint32_t delta_weight_10_i;
   uint32_t delta_weight_11_i;
   uint32_t delta_weight_12_i;
   uint32_t delta_weight_13_i;
   uint32_t delta_weight_14_i;
   uint32_t delta_weight_15_i;
   uint32_t delta_weight_16_i;
} used_global_risk_params_t;


/*   TRANSACTION TYPE = JA11  */
/*   NAMED STRUCT = 21148  */

typedef struct used_inter_month_spread
{
   char irm_id_s [12];
   uint16_t priority_n;
   char filler_2_s [2];
   int64_t charge_rm_q;
   int16_t tier_1_rm_n;
   int16_t tier_2_rm_n;
   int16_t tier_3_rm_n;
   int16_t tier_4_rm_n;
   int8_t ds_ratio_1_rm_c;
   int8_t ds_ratio_2_rm_c;
   int8_t ds_ratio_3_rm_c;
   int8_t ds_ratio_4_rm_c;
   uint8_t a_or_b_1_rm_c;
   uint8_t a_or_b_2_rm_c;
   uint8_t a_or_b_3_rm_c;
   uint8_t a_or_b_4_rm_c;
} used_inter_month_spread_t;


/*   TRANSACTION TYPE = JA11  */
/*   NAMED STRUCT = 21113  */

typedef struct used_price_params
{
   char ppr_id_s [16];
   int32_t iter_low_bound_rm_i;
   int32_t iter_high_bound_rm_i;
   uint16_t days_per_year_rm_n;
   uint8_t interest_rate_rm_c;
   uint8_t use_dividend_rm_c;
   uint8_t dividend_yield_type_c;
   uint8_t theo_pr_meth_rm_c;
   uint8_t theo_pr_meth_div_rm_c;
   uint8_t opt_price_base_1_rm_c;
   uint8_t opt_price_base_2_rm_c;
   uint8_t opt_mid_price_rm_c;
   uint8_t reverse_prices_rm_c;
   uint8_t vol_used_rm_c;
   uint8_t real_time_price_opt_rm_c;
   uint8_t real_time_price_fut_rm_c;
   uint8_t interpolation_rm_c;
   uint8_t time_dep_base_ppr_c;
} used_price_params_t;


/*   TRANSACTION TYPE = JA11  */
/*   NAMED STRUCT = 21152  */

typedef struct used_tier
{
   char tie_id_s [12];
   int32_t tier_number_i;
   int32_t max_tier_number_i;
   uint8_t reference_date_c;
   uint8_t reference_time_of_day_c;
   char filler_2_s [2];
} used_tier_t;


/*   TRANSACTION TYPE = FO23  */
/*   NAMED STRUCT = 18093  */

typedef struct withdraw_collateral_mwa_txn
{
   transaction_type_t transaction_type;
   series_t series;
   withdraw_collateral_mwa_ssi_t withdraw_collateral_mwa_ssi;
   char filler_4_s [4];
} withdraw_collateral_mwa_txn_t;


#include "oal_align_reset.h"

#endif
#ifndef __ALL_MESSAGES_H
#define __ALL_MESSAGES_H

#ifndef _BAS_MESSAGES_H_
#define _BAS_MESSAGES_H_

/******************************************************************************
Module: bas_messages.h

Message definitions generated 2020-10-21 15:24:24 by amt, version 3.19.7.0 - Built: 2017-12-30.

NOTE: Do not edit this file. It is automatically generated from
      one or more message files.
*******************************************************************************/

#define GEN_SHUT_REQ_NEWP               100001
#define GEN_SECFAIL                    -100002
#define GEN_NOPRSENTRY                 -100003
#define GEN_INVCMD                     -100005
#define GEN_AMBIGCMD                   -100007
#define GEN_INVATTRVAL                 -100008
#define GEN_NOATTRVAL                  -100010
#define GEN_TRUNCATTRVAL               -100011
#define GEN_MOREATTRVAL                -100013
#define GEN_NOCOMMAND                  -100014
#define GEN_ERRPARSE                   -100016
#define GEN_MISSENVVAR                 -100018
#define GEN_VALNOTVALID                -100020
#define GEN_MIBFULL                    -100021
#define GEN_CONTINUE_EXECUTION          100023
#define GEN_NOVALUE                    -100025
#define GEN_INVARG                     -100027
#define GEN_CMDTIMEOUT                 -100029
#define GEN_TOOMANYARG                 -100031
#define GEN_NOLOGFILE                  -100033
#define GEN_MISSARG                    -100035
#define GEN_INVARGVAL                  -100037
#define GEN_NODEFFILE                  -100038
#define GEN_TOHIGHINST                 -100040
#define GEN_PRCNOTDEF                  -100042
#define GEN_NOEXCHNAME                 -100044
#define GEN_PRCALRINMIB                -100046
#define GEN_NOCMDTHREAD                -100048
#define GEN_DEFVALTOOLONG              -100050
#define GEN_TRUNC                      -100051
#define GEN_ENVVARNOTDEF                100053
#define GEN_BADPRIORITY                -100054
#define GEN_NOSUBSYSCFG                -100056
#define GEN_FOPENERR                   -100058
#define GEN_LOGFOPENERR                -100060
#define GEN_ENVTOONESTED               -100062
#define GEN_PRCNOTEXIST                -100064
#define GEN_PRCBUSYCMD                 -100066
#define GEN_PRCBADCMDMODE              -100068
#define GEN_NODYNMEM                   -100070
#define GEN_CMDLOST                    -100072
#define GEN_NULLINP                    -100073
#define GEN_DATTIMINV                  -100075
#define GEN_DAYMONINV                  -100077
#define GEN_IMPLNOTEST                 -100079
#define GEN_INTERNALERROR              -100081
#define GEN_INVSEGMENTNR               -100083
#define GEN_INSFMEM                    -100084
#define GEN_BUGCHECK                   -100086
#define GEN_INVTRANSSIZE               -100088
#define GEN_INVTRANSTYPE               -100090
#define GEN_NOTFOU                     -100092
#define GEN_FTP_ERROR                  -100094
#define GEN_FTP_OK                      100095
#define GEN_MF_FAILUNMAP               -100096
#define GEN_MF_FNOTUNMP                -100098
#define GEN_MF_MAPFAILED               -100100
#define GEN_MF_SYNCFAILED              -100102
#define GEN_MF_MTXFAILED               -100104
#define GEN_MF_NOSUCHFILE              -100106
#define GEN_MF_EACCESS                 -100108
#define GEN_FCLOSEERR                  -100110
#define GEN_OK                          100111
#define GEN_BUFOVF                     -100112
#define GEN_IO_FAILURE                 -100114
#define GEN_IO_NOSUCHFILE              -100116
#define GEN_IO_NOACCESS                -100118
#define GEN_IO_INVRESOURCE             -100120
#define GEN_IO_BUFTOSMALL              -100122
#define GEN_NOT_SUPPORTED              -100124
#define GEN_ABORT_MESSAGES             -100126
#define GEN_RT_ERRALLOMEM              -105000
#define GEN_RT_ERRFACNAM               -105002
#define GEN_RT_ERRDATPTYP              -105004
#define GEN_RT_KEYTYPNOTSUP            -105006
#define GEN_RT_PROTOCOLERR             -105008
#define GEN_RT_TRUNCATED               -105010
#define GEN_RT_FLAGOUTRANG             -105012
#define GEN_RT_INVEVTNAM               -105014
#define GEN_RT_NOTALLOW                -105016
#define GEN_RT_ABORT                   -105018
#define GEN_RT_TOOMANYDATP             -105020
#define GEN_RT_FLAGMISS                -105022
#define GEN_RT_INVDATPLEN              -105024
#define GEN_RT_NOTINIT                 -105026
#define GEN_RT_UNKPARNAME              -105028
#define GEN_RT_PARCNT                  -105030
#define GEN_RT_BADPARAM                -105032
#define GEN_RT_INTOVF                  -105034
#define GEN_RT_INVTXNUMBER             -105036
#define GEN_RT_INVTXTYPE               -105038
#define GEN_SEC_OK                      120001
#define GEN_SEC_NYI                    -120003
#define GEN_SEC_FAIL                   -120004
#define GEN_SEC_INVID                  -120006
#define GEN_SEC_INVIDENT               -120008
#define GEN_SEC_TABFULL                -120010
#define GEN_SEC_FILTOOSMALL            -120012
#define GEN_SEC_SECTOOSMALL            -120014
#define GEN_LCK_OK                      125001
#define GEN_LCK_NYI                    -125003
#define GEN_LCK_INVID                  -125004
#define GEN_LCK_TABFULL                -125006
#define GEN_TIM_CTRY_NOT_FOUND         -130000
#define GEN_TIM_NOT_INIT               -130002
#define GEN_TIM_NULL                    130003
#define GEN_TIM_DELTA_NOT_ALLOWED       130005
#define GEN_TIM_TZ_NOT_SET             -130006
#define GEN_PRICE_NORMAL                131001
#define GEN_PRICE_NYI                  -131003
#define GEN_PRICE_BADFRAC1             -131004
#define GEN_PRICE_BADFRAC2             -131006
#define GEN_PRICE_BADFRACVAL           -131008
#define GEN_PRICE_BADFRACDIV           -131010
#define GEN_PRICE_INVFRACBAS           -131012
#define GEN_PRICE_INVFMTNO             -131014
#define GEN_PRICE_FMTREQ               -131016
#define GEN_PRICE_INVDECPRICE          -131018
#define OMNI_SYNCHPOINT                -145000
#define OMNI_SECURITY                  -145002
#define OMNI_LOGIN_FAIL                -145004
#define OMNI_NOT_NOTIFIED              -145005
#define OMNI_DUPL_LOGIN                -145006
#define OMNI_UNKNOWNBYBE               -145008
#define OMNI_OAPIOLD                   -145010
#define OMNI_TIMED_OUT                 -145011
#define GEN_RTR_ERRALLOMEM             -165000
#define GEN_RTR_ERRFACNAM              -165002
#define GEN_RTR_ERRDATPTYP             -165004
#define GEN_RTR_KEYTYPNOTSUP           -165006
#define GEN_RTR_PROTOCOLERR            -165008
#define GEN_RTR_TRUNCATED              -165010
#define GEN_RTR_FLAGOUTRANG            -165012
#define GEN_RTR_INVEVTNAM              -165014
#define GEN_RTR_NOTALLOW               -165016
#define GEN_RTR_ABORT                  -165018
#define GEN_RTR_TOOMANYDATP            -165020
#define GEN_RTR_FLAGMISS               -165022
#define GEN_RTR_INVDATPLEN             -165024
#define GEN_RTR_NOTINIT                -165026
#define GEN_RTR_UNKPARNAME             -165028
#define GEN_RTR_PARCNT                 -165030
#define GEN_RTR_BADPARAM               -165032
#define GEN_RTR_INTOVF                 -165034
#define GEN_RTR_INVTXNUMBER            -165036
#define GEN_RTR_INVTXTYPE              -165038
#define GEN_RTR_SRVABOTX               -165040
#define GEN_RTR_NOSRVAVL                165041
#define GEN_RTR_INVFLAGS               -165042
#define GEN_RTR_INVCHANNEL             -165044
#define GEN_RTR_INVFACNAM              -165046
#define GEN_RTR_FAILED                 -165048
#define GEN_TPS_NOHOST                 -166000
#define GEN_TPS_ERRLOCLNAME            -166002
#define GEN_TPS_BADIPADDR              -166004
#define GEN_TPS_ERRHOSTNAME            -166006
#define GEN_TPS_ERROPENSOCK            -166008
#define GEN_TPS_ERRTHREAD              -166010
#define GEN_TPS_ERRTCPCONN             -166012
#define GEN_TPS_INVHANDLE              -166014
#define GEN_TPS_INVBUFFER              -166016
#define GEN_TPS_NOCALLBACK             -166018
#define GEN_TPS_INSMEM                 -166020
#define GEN_TPS_COMMERR                -166022
#define GEN_TPS_INSBUFF                -166024
#define GEN_TPS_INVSEM                 -166026
#define GEN_TPS_ERRBIND                -166028
#define GEN_TPS_ERRLSTN                -166030
#define GEN_TPS_INVOCVER               -166032
#define GEN_TPS_INVMODE                -166034
#define GEN_TPS_EOF                    -166036
#define BAS_HASH_FEWBUCKETS            -167000
#define BAS_HASH_BADTYPE               -167002
#define BAS_HASH_ITEMEXISTS            -167003
#define BAS_HASH_BADLISTCMD            -167004
#define BAS_HASH_NOCMPFUN              -167006
#define BAS_HASH_NOHASHFUN             -167008
#define BAS_HASH_MALFUNC               -167010
#define BAS_PWD_OK                      167501
#define BAS_PWD_INTERR                 -167502
#define BAS_PWD_AESERR                 -167504
#define BAS_PWD_BASE64ERR              -167506
#define BAS_PWD_KEY_FILE_NOT_FOUND     -167508
#define BAS_PWD_KEY_FILE_CORRUPT       -167510
#define BAS_PWD_KEY_FILE_EXISTS        -167512
#define BAS_PWD_INV_CHAR_IN_PWD        -167514
#define BAS_PWD_CONFIGDIR_NOT_FOUND    -167516
#define BAS_PWD_ERR_RENAME_KEY_FILE    -167518
#define BAS_PWD_BUFF_TO_SMALL          -167520
#define BAS_CMD_NOCOMMAND              -168000
#define BAS_CMD_INVALIDCMD             -168002
#define BAS_CMD_TOOLONGITEM            -168004
#define BAS_CMD_NOATTRVAL              -168006
#define BAS_CMD_TOOLONGAVAL            -168008
#define BAS_CMD_NOPRSENTRY             -168010
#define BAS_CMD_AMBIGCMD               -168012
#define BAS_CMD_TRUNCATTRVAL           -168014
#define BAS_CMD_CMDFILEERR             -168016
#define BAS_CMD_INVARG                 -168017
#define OAL_ILLEGAL_PARAMETER          -169000
#define OAL_OVERFLOW                   -169002
#define OAL_ERROR                      -169004
#define BAS_MDF_VERSION                 198001

/******************************************************************************
*end*of* bas_messages.h
*******************************************************************************/

#endif /* _BAS_MESSAGES_H_ */


#ifndef _CDB_MESSAGES_H_
#define _CDB_MESSAGES_H_

/******************************************************************************
Module: cdb_messages.h

Message definitions generated 2020-10-21 15:24:26 by amt, version 3.19.7.0 - Built: 2017-12-30.

NOTE: Do not edit this file. It is automatically generated from
      one or more message files.
*******************************************************************************/

#define CDB_SUCCCOMP                    300001
#define CDB_NORMAL                      300003
#define CDB_NOMAREXIST                 -300005
#define CDB_NOCOUEXIST                 -300007
#define CDB_NOMSUEXIST                 -300009
#define CDB_INSFMEM                    -300010
#define CDB_SQLDECLERR                 -300012
#define CDB_SQLERROR                   -300014
#define CDB_UNTRTNO                    -300016
#define CDB_ILLEXPYEAR                 -300018
#define CDB_NOTBLMATCH                 -300020
#define CDB_USRNOTEXIST                -300022
#define CDB_WRONGACCTYPE               -300024
#define CDB_NOVALIDUST                 -300026
#define CDB_NOVALIDUSR                 -300028
#define CDB_USRNOTLEG                  -300030
#define CDB_SECMISMTC                  -300032
#define CDB_USER_TIMEOUT               -300034
#define CDB_USER_LOST                  -300036
#define CDB_OLDTIMESEC                 -300038
#define CDB_MNUNOTEXIST                -300040
#define CDB_ILLEXPMONTH                -300042
#define CDB_DBRETRY                    -300044
#define CDB_VECFULL                    -300046
#define CDB_BUGCHECK                   -300048
#define CDB_TOOMANYUSERS               -300050
#define CDB_TOOMANYSESSION             -300052
#define CDB_NUMSESSIONTOOLOW           -300054
#define CDB_PARSESSNOTALLOWED          -300056
#define CDB_NOICOEXIST                  300057
#define CDB_NOITUEXIST                  300059
#define CDB_NOLTFEXIST                  300061
#define CDB_NOPQREXIST                  300063
#define CDB_NOTRFEXIST                  300065
#define CDB_NOVMSEXIST                  300067
#define CDB_NOVOLEXIST                  300069
#define CDB_NOPSCEXIST                  300071
#define CDB_NOCOPEXIST                  300073
#define CDB_NOCBSEXIST                 -300075
#define CDB_NOCOMEXIST                 -300077
#define CDB_NOIDBEXIST                 -300079
#define CDB_NOIDLEXIST                 -300081
#define CDB_NOINSEXIST                 -300083
#define CDB_NOINTEXIST                 -300085
#define CDB_NOLITEXIST                 -300087
#define CDB_NOLTTEXIST                 -300089
#define CDB_NOLTUEXIST                 -300091
#define CDB_NOTRLEXIST                 -300093
#define CDB_NOTRSEXIST                 -300095
#define CDB_NOTSFEXIST                 -300097
#define CDB_NOTRTEXIST                 -300099
#define CDB_NOTZOEXIST                 -300101
#define CDB_NOUSREXIST                 -300103
#define CDB_NOUSTEXIST                 -300105
#define CDB_NOVBSEXIST                 -300107
#define CDB_NOVPTEXIST                 -300109
#define CDB_NOMNUACCESS                -300111
#define CDB_USRNOTLOG                  -300113
#define CDB_NOPREVINA                  -300115
#define CDB_NOCLHEXIST                 -300117
#define CDB_NOMEMEXIST                 -300119
#define CDB_NOINCEXIST                 -300121
#define CDB_NOCLIEXIST                 -300123
#define CDB_NOBBOEXIST                 -300125
#define CDB_NOCRSEXIST                 -300127
#define CDB_NOSPREXIST                 -300129
#define CDB_NOTRCEXIST                 -300131
#define CDB_NOTRREXIST                 -300133
#define CDB_NOOBLEXIST                 -300135
#define CDB_NOLFAEXIST                 -300137
#define CDB_NONODEXIST                 -300139
#define CDB_NOLNOEXIST                 -300141
#define CDB_NOISSEXIST                  300143
#define CDB_NOCSSEXIST                  300145
#define CDB_NOPCOEXIST                  300147
#define CDB_NOPICEXIST                  300149
#define CDB_NOPISEXIST                  300151
#define CDB_NOPRDEXIST                  300153
#define CDB_NOPSREXIST                  300155
#define CDB_NOPUREXIST                  300157
#define CDB_NOUCLEXIST                  300159
#define CDB_NOWINEXIST                  300161
#define CDB_NOVPDEXIST                  300163
#define CDB_NOISDEXIST                  300165
#define CDB_NOISCEXIST                  300167
#define CDB_NOCOGEXIST                  300169
#define CDB_NOFMLEXIST                  300171
#define CDB_NOSYIEXIST                  300173
#define CDB_NOOBKEXIST                  300175
#define CDB_NOTSREXIST                  300177
#define CDB_NOEDGEXIST                  300179
#define CDB_NOSPGEXIST                  300181
#define CDB_NOPDPEXIST                  300183
#define CDB_NOFOVEXIST                  300185
#define CDB_NOCLPEXIST                  300187
#define CDB_NOCLHUSR                   -300189
#define CDB_NOAFTEXIST                 -300191
#define CDB_NOATYEXIST                 -300193
#define CDB_NOADCEXIST                 -300195
#define CDB_NOCSBEXIST                 -300197
#define CDB_NOEXCEXIST                 -300199
#define CDB_NOFASEXIST                 -300201
#define CDB_NOFTBEXIST                 -300203
#define CDB_NONTDEXIST                 -300205
#define CDB_NOPEVEXIST                 -300207
#define CDB_NOPFTEXIST                 -300209
#define CDB_NOTRUEXIST                 -300211
#define CDB_INVCOMMAND                 -300213
#define CDB_NOSYMEXIST                 -300215
#define CDB_NOACCEXIST                 -300217
#define CDB_NOSBSEXIST                 -300219
#define CDB_WRONGWEEK                  -300220
#define CDB_SLEC_INSERR                -300222
#define CDB_SLEC_EXCMISSING            -300224
#define CDB_SLEC_DIFFCODE              -300226
#define CDB_SLEC_DIFFISIN              -300228
#define CDB_NODLVEXIST                 -300229
#define CDB_NOCOMSPEC                  -300230
#define CDB_ERRLONGCOM                 -300232
#define CDB_NOMARSPEC                  -300234
#define CDB_ERRLONGMAR                 -300236
#define CDB_NOINGSPEC                  -300238
#define CDB_ERRLONGING                 -300240
#define CDB_ERRLONGINS                 -300242
#define CDB_NOSTRKSPEC                 -300244
#define CDB_ERRLONGSTRK                -300246
#define CDB_NOSTRKDECSPEC              -300248
#define CDB_ERRLONGSTRKDEC             -300250
#define CDB_NOCONTRSPEC                -300252
#define CDB_ERRLONGCONTR               -300254
#define CDB_NOCONTRDECSPEC             -300256
#define CDB_ERRLONGCONTRDEC            -300258
#define CDB_NOEXPSPEC                  -300260
#define CDB_ERRLONGEXP                 -300262
#define CDB_ERRLONGLTD                 -300264
#define CDB_ERRLONGLTT                 -300266
#define CDB_ERRLONGISIN                -300268
#define CDB_ERRLONGIMPLD               -300270
#define CDB_ERRLONGIMPLT               -300272
#define CDB_NOOPERSPEC                 -300274
#define CDB_ERRLONGOPER                -300276
#define CDB_ERRLONGDLVSTART            -300278
#define CDB_ERRLONGDLVSTOP             -300280
#define CDB_ERRLONGSTART               -300282
#define CDB_ERRLONGEND                 -300284
#define CDB_ERRLONGSYMB                -300286
#define CDB_ERRLONGMTH                 -300288
#define CDB_ERRLONGSTR                 -300290
#define CDB_ERRLONGEXC                 -300292
#define CDB_ERRLONGSTATUS              -300294
#define CDB_ERRLONGLISTING             -300296
#define CDB_ERRLONGTRINCL              -300298
#define CDB_ERRLONGISTRADED            -300300
#define CDB_ERRTRINCL                  -300302
#define CDB_ERRISTRADED                -300304
#define CDB_WRONGINPUT                  300305
#define CDB_NOSERIES                    300307
#define CDB_NOINSTRUMENT                300309
#define CDB_NOUNDERLYING                300311
#define CDB_NOCOMBO                     300313
#define CDB_NOUSER                      300315
#define CDB_MARCLOSED                   300317
#define CDB_COUCLOSED                   300319
#define CDB_NOTRM                       300321
#define CDB_NOMARKET                    300323
#define CDB_NOINSTGROUP                 300325
#define CDB_UNEXPECTED                 -300326
#define CDB_WRONGSEGM                  -300328
#define CDB_NOINSTCLASS                 300329
#define CDB_NOBASEDFOUND               -300330
#define CDB_NOACCOUNT                   300331
#define CDB_NOSYMBOL                    300333
#define CDB_WRONGEXP                   -300334
#define CDB_ILLEGTRD                   -300336
#define CDB_WRONGCOM                   -300338
#define CDB_DUMMY                      -300340
#define CDB_RTRERROR                   -300342
#define CDB_ABORT                      -300344
#define CDB_ILLCHANNEL                 -300346
#define CDB_NOSRVAVAIL                 -300348
#define CDB_INSERTFAILED               -300350
#define CDB_REMOVEFAILED               -300352
#define CDB_NOTFOUNDDB                 -300354
#define CDB_NOTFOUNDMEM                -300356
#define CDB_UCLEXCEED                  -300358
#define CDB_NOTAREPO                   -300360
#define CDB_NOTMPLFOUND                -300362
#define CDB_STARTWRONG                 -300364
#define CDB_STARTNOTSETTL              -300366
#define CDB_ENDWRONG                   -300368
#define CDB_ENDNOTSETTL                -300370
#define CDB_WRONGMONEYPAR              -300372
#define CDB_WRONGNOOFSUB               -300374
#define CDB_WRONGBUYSELLBACK           -300376
#define CDB_NOINCFOUND                 -300378
#define CDB_REPOALREXIST                300379
#define CDB_REPOTOOLONG                -300380
#define CDB_LOADFAILED                 -300382
#define CDB_STARTNOTVALID              -300384
#define CDB_ENDNOTVALID                -300386
#define CDB_OUTRSPECMISSING            -300388
#define CDB_STARTBEFISSUE              -300390
#define CDB_ENDAFTERMATUR              -300392
#define CDB_SERIESALREXIST              300393
#define CDB_TMNOTALLOWED               -300394
#define CDB_INSEMPTY                   -300396
#define CDB_NOCTDPRICE                 -300398
#define CDB_INSNOTFOUND                -300400
#define CDB_ENDAFTEREQMATUR            -300402
#define CDB_NOTENOUGHLEGS              -300404
#define CDB_COMBONOTTM                 -300406
#define CDB_NOCONVFACTOR               -300408
#define CDB_ADDISIN                     300409
#define CDB_STARTTOEARLY               -300410
#define CDB_ENDTOEARLY                 -300412
#define CDB_PASSWLENTOOSHORT           -300414
#define CDB_PASSWINHISTORY             -300416
#define CDB_BOXALREXIST                 300417
#define CDB_NOTEMPLATEBOX              -300418
#define CDB_TMBOXNOTALLOWED            -300420
#define CDB_TOO_MANY_TM_COMBOS         -300421
#define CDB_COMBODIFFPART              -300422
#define CDB_CURRISNOTEQ                -300424
#define CDB_NODSCEXIST                 -300425
#define CDB_TRANSNOTINLTT              -300426
#define CDB_TRANSNOTOPEN               -300428
#define CDB_PRCQUOTISNOTEQ             -300430
#define CDB_HPFILENOTFOUND             -300432
#define CDB_HPOUTPUTFILEWRONG          -300434
#define CDB_DICFILENOTFOUND             300435
#define CDB_SEGMENTFULL                 300437
#define CDB_MAXTWOLEGEXCEEDED          -300438
#define CDB_MAXTHREELEGEXCEEDED        -300440
#define CDB_LASTTRADINGISPASSED        -300442
#define CDB_CSTNOTAUTH                 -300444
#define CDB_FIRSTTRADINGINFUTURE       -300446
#define CDB_OPERNOTVALID               -300448
#define CDB_STATUSNOTVALID             -300450
#define CDB_WRONGUST                   -300452
#define CDB_WRONGMAC                   -300454
#define CDB_WRONGAPPL                  -300456
#define CDB_WRONGRWACCESS              -300458
#define CDB_WRONGMENUACCESS            -300460
#define CDB_NOTAUTHMAC                 -300462
#define CDB_NOTAUTHUSR                 -300464
#define CDB_USERALREXIST               -300466
#define CDB_MACALREXIST                -300468
#define CDB_ERRLONGFTD                 -300470
#define CDB_ERRLONGFTT                 -300472
#define CDB_CUSTNOTAUTH                -300474
#define CDB_NOTSETTL                   -300476
#define CDB_TMINSTNOTALLOWED           -300478
#define CDB_EXPNOTSETTL                -300480
#define CDB_EXPDATEWRONG               -300482
#define CDB_WRONGNOOFSTRIP             -300484
#define CDB_EXPNOTTRD                  -300486
#define CDB_MAXPARTDEFINEDEXCEEDED     -300488
#define PD_ACTIVE                       305001
#define PD_EXPISNTD                    -305002
#define PD_LTRISNTD                     305003
#define PD_ALREADYRESUMED               305005
#define PD_ALREADYSUSP                  305007
#define PD_ALREADYEXIST                 305009
#define PD_NOTEXIST                     305011
#define PD_SGNTXSTART                   305013
#define PD_BUFOVFLOW                   -305015
#define PD_UNEXPECTED                  -305016
#define PD_HIGHISINNOTCORR             -305018
#define PD_LOWISINNOTCORR              -305020
#define PD_LOWERISHIGHER               -305022
#define PD_ISINOLAP                    -305024
#define PD_ISINMISS                    -305026
#define PD_SEGMZERO                    -305028
#define PD_INVONOFF                    -305030
#define PD_SERCODEEMPTY                -305032
#define PD_INGCODEZERO                 -305034
#define PD_MARCODEZERO                 -305036
#define PD_OPERNOTVALID                -305038
#define PD_DELNOTVALID                 -305040
#define PD_ISINNOTUNIQUE               -305042
#define PD_WRONGIMPLFORMAT             -305044
#define PD_WRONGEXPFORMAT              -305046
#define PD_WRONGLASTFORMAT             -305048
#define PD_ORIGSERNOTFOUND             -305050
#define PD_UPPSERNOTFOUND              -305052
#define PD_EXTSERIESTRT                -305054
#define PD_NOTACTIVE                   -305056
#define PD_NOTFOUND                    -305058
#define PD_FUTDELETE                   -305060
#define PD_NOTAUTHORIZED               -305062
#define PD_ILLKEYVALUE                 -305064
#define PD_SPACESINKEY                 -305066
#define PD_ILLSEARCHVALUE              -305068
#define PD_FIELDISEMPTY                -305070
#define PD_COMCODEALREXIST             -305072
#define PD_COMIDALREXIST               -305074
#define PD_INGCODEALREXIST             -305076
#define PD_INGIDALREXIST               -305078
#define PD_INTCODEALREXIST             -305080
#define PD_INTIDALREXIST               -305082
#define PD_INCCODEALREXIST             -305084
#define PD_INCIDALREXIST               -305086
#define PD_INSCODEALREXIST             -305088
#define PD_INSIDALREXIST               -305090
#define PD_INSMUSTBESAME               -305092
#define PD_MARCODEALREXIST             -305094
#define PD_MARIDALREXIST               -305096
#define PD_EXCCODEALREXIST             -305098
#define PD_EXCIDALREXIST               -305100
#define PD_CBGCODEALREXIST             -305102
#define PD_CBGIDALREXIST               -305104
#define PD_CBTCODEALREXIST             -305106
#define PD_CBTIDALREXIST               -305108
#define PD_CBCCODEALREXIST             -305110
#define PD_CBCIDALREXIST               -305112
#define PD_CBSCODEALREXIST             -305114
#define PD_CBSIDALREXIST               -305116
#define PD_WRONGPERIOD                 -305118
#define PD_EXPNOTLEG                   -305120
#define PD_DELNOTFOUND                 -305122
#define PD_TIMEISNULL                  -305124
#define PD_NOTEXACT                    -305126
#define PD_TIMEISPASSED                -305128
#define PD_INCNOTTRADED                -305130
#define PD_WRONGISIN                   -305132
#define PD_COMILLSTATUS                -305134
#define PD_ILLPASSW                    -305136
#define PD_INSILLSTATUS                -305138
#define PD_EXPISPASSED                 -305140
#define PD_STRIKEISZERO                -305142
#define PD_STRIKENOTZERO               -305144
#define PD_IDNOTCREATED                -305146
#define PD_OPRANOTUNIQUE               -305148
#define PD_OPRASTRKNOTUNIQUE           -305150
#define PD_REMOVENOTALLWD              -305152
#define PD_FIELDEXCEEDED               -305154
#define PD_DOUBLEMENU                  -305156
#define PD_DOUBLEMENUTXT               -305158
#define PD_MNUNOTCHGABLE               -305160
#define PD_USRNOTFOUND                 -305162
#define PD_ACTNOTFOUND                 -305164
#define PD_MTXNOTFOUND                 -305166
#define PD_MACNOTFOUND                 -305168
#define PD_MNUNOTFOUND                 -305170
#define PD_BONDPARAM                   -305172
#define PD_POWPARAM                    -305174
#define PD_POWSTARTGTSTOP              -305176
#define PD_DOUBLECUPDATE               -305178
#define PD_BOTHWINSUM                  -305180
#define PD_SUMAFTERWIN                 -305182
#define PD_STOPAFTERREST               -305184
#define PD_DOUBLECOM                   -305186
#define PD_DOUBLESUMDATE               -305188
#define PD_DOUBLEWINDATE               -305190
#define PD_DOUBLESTOPDATE              -305192
#define PD_DOUBLERESTDATE              -305194
#define PD_DOUBLEINS                   -305196
#define PD_DOUBLESIZE                  -305198
#define PD_DOUBLEMODIFIER              -305200
#define PD_DOUBLESPREAD                -305202
#define PD_DOUBLELOWER                 -305204
#define PD_DOUBLEUPPER                 -305206
#define PD_LOWERGEUPPER                -305208
#define PD_LOWEROVRLAP                 -305210
#define PD_UPPEROVRLAP                 -305212
#define PD_DOUBLEMONTH                 -305214
#define PD_DOUBLEPERIOD                -305216
#define PD_DOUBLEORDERNO               -305218
#define PD_ILLEGMONTH                  -305220
#define PD_ILLEGPERIOD                 -305222
#define PD_DOUBLEEXP                   -305224
#define PD_WRONGEXP                    -305226
#define PD_WRONGNOT                    -305228
#define PD_WRONGLIFETIME               -305230
#define PD_DOUBLELEG                   -305232
#define PD_SERIEISPASSED               -305234
#define PD_LTDISPASSED                 -305236
#define PD_TOOFEWLEGS                  -305238
#define PD_CBCNOTTRADED                -305240
#define PD_DOUBLEINC                   -305242
#define PD_DOUBLEWIN                   -305244
#define PD_DOUBLEPEV                   -305246
#define PD_SERIESNOTEXIST              -305248
#define PD_DISCEXCEED                  -305250
#define PD_DOUBLEFVL                   -305252
#define PD_FVLNOTEXIST                 -305254
#define PD_DOUBLEFTB                   -305256
#define PD_FEEVALEXCEED                -305258
#define PD_LIMITSEARCH                 -305260
#define PD_ILLEGMONTHNAME              -305262
#define PD_ILLEGPERIODNAME             -305264
#define PD_DOUBLELGP                   -305266
#define PD_DOUBLETRU                   -305268
#define PD_WROPEN                      -305270
#define PD_WRNET                       -305272
#define PD_DOUBLECHA                   -305274
#define PD_DOUBLECLI                   -305276
#define PD_EXCWCNOTALLWD               -305278
#define PD_DOUBLESPR                   -305280
#define PD_SPRCHKLEG                   -305282
#define PD_TRRCODEEMPTY                -305284
#define PD_CONDEMPTY                   -305286
#define PD_SPRCHKEMPTY                 -305288
#define PD_PUBINFEMPTY                 -305290
#define PD_DOUBLETRC                   -305292
#define PD_DOUBLEPRDDATE               -305294
#define PD_ACCNUMALREXIST              -305296
#define PD_DOUBLETRT                   -305298
#define PD_WRACTTIME                   -305300
#define PD_WRCONTROP                   -305302
#define PD_WRCONTRFACSUB               -305304
#define PD_WRCONTRFAC                  -305306
#define PD_DOUBLEISD                   -305308
#define PD_ISDNOTEQ                    -305310
#define PD_WRSERIES                    -305312
#define PD_DOUBLEINSID                 -305314
#define PD_DOUBLESOINSID               -305316
#define PD_OLDINSNOTEXIST              -305318
#define PD_CODEISEQ                    -305320
#define PD_SOCODEISEQ                  -305322
#define PD_INSINPREV                   -305324
#define PD_PASSEDDATE                  -305326
#define PD_ALREXIST                    -305328
#define PD_NOCHGALW                    -305330
#define PD_EXCEEDCONTR                 -305332
#define PD_NAMEISEQ                    -305334
#define PD_SOOLDNAMEISEQ               -305336
#define PD_SONEWNAMEISEQ               -305338
#define PD_WRINFSRC                    -305340
#define PD_INFSRCNACT                  -305342
#define PD_WRINFTYPE                   -305344
#define PD_WRONGATTR                   -305346
#define PD_WRONGGENATTR                -305348
#define PD_WRONGDERATTR                -305350
#define PD_BOTHATTR                    -305352
#define PD_BOTHCOMEXP                  -305354
#define PD_ISSALREXIST                 -305356
#define PD_ISSNOSERIES                 -305358
#define PD_DOUBLEMNA                   -305360
#define PD_DOUBLEINT                   -305362
#define PD_DOUBLECBT                   -305364
#define PD_FROMTOP                     -305366
#define PD_FROMTOR                     -305368
#define PD_FROMTOI                     -305370
#define PD_FRPBLANK                    -305372
#define PD_FRPNOTBLANK                 -305374
#define PD_FRRBLANK                    -305376
#define PD_FRRNOTBLANK                 -305378
#define PD_WHPBLANK                    -305380
#define PD_WHPNOTBLANK                 -305382
#define PD_WHRBLANK                    -305384
#define PD_WHRNOTBLANK                 -305386
#define PD_OTHQBLANK                   -305388
#define PD_OTHBNOTBLANK                -305390
#define PD_OTHBBLANK                   -305392
#define PD_OTHQNOTBLANK                -305394
#define PD_DOUBLPFT                    -305396
#define PD_BUYSELL                     -305398
#define PD_RESP                        -305400
#define PD_ISNNODIG                    -305402
#define PD_MAXISIN                     -305404
#define PD_WRONGCBA                    -305406
#define PD_NODLVFOUND                  -305408
#define PD_NODLVEXPFOUND               -305410
#define PD_IFILL                       -305412
#define PD_INSDUP                      -305414
#define PD_NOSTORE                     -305416
#define PD_SGNTOMGRP                   -305418
#define PD_SGNTOMSER                   -305420
#define PD_SGNTOMNEWSER                -305422
#define PD_SGNTOMSTRK                  -305424
#define PD_SGNUNDZERO                  -305426
#define PD_SGNONGTX                    -305428
#define PD_EXPINVDAY                   -305430
#define PD_EXPINVWEEK                  -305432
#define PD_EXPINVMTH                   -305434
#define PD_ISNCODEALREXIST             -305436
#define PD_ISNIDALREXIST               -305438
#define PD_TRRCODEALREXIST             -305440
#define PD_TRRIDALREXIST               -305442
#define PD_COMCODEZERO                 -305444
#define PD_DEFMUSTBEOPEN               -305446
#define PD_MUSTBEOPEN                  -305448
#define PD_NOFLTITEM                   -305450
#define PD_DOUBLEQUA                   -305452
#define PD_DOUBLEBAS                   -305454
#define PD_DOUBLEOTHBAS                -305456
#define PD_DOUBLEOTHQUA                -305458
#define PD_NOPVTITEM                   -305460
#define PD_NOLITITEM                   -305462
#define PD_CBTANDINT                   -305464
#define PD_NOMACITEM                   -305466
#define PD_NOMNUITEM                   -305468
#define PD_DOUBLESBS                   -305470
#define PD_ERRFROMATY                  -305472
#define PD_DOUBLEPERCODE               -305474
#define PD_DOUBLEPERNAME               -305476
#define PD_ILLEGDATE                   -305478
#define PD_LTTSTATUSUNL                -305480
#define PD_LTTSTARTTIMEEMPTY           -305482
#define PD_LTTSTARTTIMENOTEMPTY        -305484
#define PD_LTTSTOPTIMEEMPTY            -305486
#define PD_LTTSTOPTIMENOTEMPTY         -305488
#define PD_NOISSSERIES                 -305490
#define PD_INCANDINS                   -305492
#define PD_NOEXPINS                    -305494
#define PD_INVPQREXP                   -305496
#define PD_VOLLSTEMPTY                 -305498
#define PD_HLSTEMPTY                   -305500
#define PD_HDLMEMPTY                   -305502
#define PD_TIMBEFALEMPTY               -305504
#define PD_TIMBETWALEMPTY              -305506
#define PD_CSTNOTALLWD                 -305508
#define PD_VOLANDLST                   -305510
#define PD_WRONGCONTR                  -305512
#define PD_NOPFTITEM                   -305514
#define PD_ALLFEEVALEMPTY              -305516
#define PD_PQRDELNOTVALID              -305518
#define PD_UNDALREADYRESUMED           -305520
#define PD_UNDALREADYSUSP              -305522
#define PD_CSTALREADYRESUMED           -305524
#define PD_CSTALREADYSUSP              -305526
#define PD_WACCNOTALLOWED              -305528
#define PD_INSDEL                      -305530
#define PD_EXPWEEKEMPTY                -305532
#define PD_EXPMTHEMPTY                 -305534
#define PD_CBRSTPEXCEED                -305536
#define PD_CBRINCSTEPS                 -305538
#define PD_NOCLIITEM                   -305540
#define PD_INSISDELETED                -305542
#define PD_OBLDOUBLE                   -305544
#define PD_OBLRWDOUBLE                 -305546
#define PD_ISINCODEEMPTY               -305548
#define PD_DOUBLENOD                   -305550
#define PD_DOUBLEFAC                   -305552
#define PD_USERLOCK                    -305554
#define PD_SLECCOMINCOMPL              -305556
#define PD_ISINTSYSEMPTY               -305558
#define PD_MODIFIEREMPTY               -305560
#define PD_ISSIDENTEMPTY               -305562
#define PD_COGCODEALREXIST             -305564
#define PD_COGIDALREXIST               -305566
#define PD_OBKCODEALREXIST             -305568
#define PD_OBKIDALREXIST               -305570
#define PD_DOUBLEFML                   -305572
#define PD_POSORTRDEXIST               -305574
#define PD_NOCLAVAIL                   -305576
#define PD_PMMANDCGM                   -305578
#define PD_DOUBLECGM                   -305580
#define PD_GUARDPRICEEMPTY             -305582
#define PD_VALINTTYPEEMPTY             -305584
#define PD_VALINTBASEEMPTY             -305586
#define PD_GROSSMARGPROPEMPTY          -305588
#define PD_DELIVPROPEMPTY              -305590
#define PD_DOUBLEREG                   -305592
#define PD_DOUBLEREGDESC               -305594
#define PD_NOACC                       -305596
#define PD_NOACCACT                    -305598
#define PD_NOACRACC                    -305600
#define PD_NOACRACCACT                 -305602
#define PD_NOING                       -305604
#define PD_NOINGACT                    -305606
#define PD_NOCLH                       -305608
#define PD_NOCLHACT                    -305610
#define PD_NOORG                       -305612
#define PD_NOORGACT                    -305614
#define PD_NOCCCST                     -305616
#define PD_NOCCCSTACT                  -305618
#define PD_NOMAR                       -305620
#define PD_NOMARACT                    -305622
#define PD_NOMSU                       -305624
#define PD_NOMSUACT                    -305626
#define PD_NOINS                       -305628
#define PD_NOINSACT                    -305630
#define PD_NOUPPINS                    -305632
#define PD_NOUPPINSACT                 -305634
#define PD_NOFIXINS                    -305636
#define PD_NOFIXINSACT                 -305638
#define PD_NOINT                       -305640
#define PD_NOINTACT                    -305642
#define PD_NOUPPINT                    -305644
#define PD_NOUPPINTACT                 -305646
#define PD_NOCBC                       -305648
#define PD_NOCBCACT                    -305650
#define PD_NOCBG                       -305652
#define PD_NOCBGACT                    -305654
#define PD_NOCBR                       -305656
#define PD_NOCBRACT                    -305658
#define PD_NOCBT                       -305660
#define PD_NOCBTACT                    -305662
#define PD_NOMNU                       -305664
#define PD_NOMNUACT                    -305666
#define PD_NOATYPE                     -305668
#define PD_NOATYPEACT                  -305670
#define PD_NOCIS                       -305672
#define PD_NOCISACT                    -305674
#define PD_NOCOM                       -305676
#define PD_NOCOMACT                    -305678
#define PD_NONEWCOM                    -305680
#define PD_NONEWCOMACT                 -305682
#define PD_NOBRD                       -305684
#define PD_NOBRDACT                    -305686
#define PD_NOPRICBA                    -305688
#define PD_NOPRICBAACT                 -305690
#define PD_NOSECCBA                    -305692
#define PD_NOSECCBAACT                 -305694
#define PD_NODLSCBA                    -305696
#define PD_NODLSCBAACT                 -305698
#define PD_NOALTCOM                    -305700
#define PD_NOALTCOMACT                 -305702
#define PD_NOINC                       -305704
#define PD_NOINCACT                    -305706
#define PD_NOUPPINC                    -305708
#define PD_NOUPPINCACT                 -305710
#define PD_NOACCTYP                    -305712
#define PD_NOACCTYPACT                 -305714
#define PD_NOEXC                       -305716
#define PD_NOEXCACT                    -305718
#define PD_NOCUR                       -305720
#define PD_NOCURACT                    -305722
#define PD_NOCST                       -305724
#define PD_NOCSTACT                    -305726
#define PD_NOPAYCST                    -305728
#define PD_NOPAYCSTACT                 -305730
#define PD_NOCC1CST                    -305732
#define PD_NOCC1CSTACT                 -305734
#define PD_NOCC2CST                    -305736
#define PD_NOCC2CSTACT                 -305738
#define PD_NOUST                       -305740
#define PD_NOUSTACT                    -305742
#define PD_NOUSR                       -305744
#define PD_NOUSRACT                    -305746
#define PD_NOLAN                       -305748
#define PD_NOLANACT                    -305750
#define PD_NOCOU                       -305752
#define PD_NOCOUACT                    -305754
#define PD_NOBSS                       -305756
#define PD_NOBSSACT                    -305758
#define PD_NOEXP                       -305760
#define PD_NOEXPACT                    -305762
#define PD_NOLST                       -305764
#define PD_NOLSTACT                    -305766
#define PD_NOSPS                       -305768
#define PD_NOSPSACT                    -305770
#define PD_NOVPT                       -305772
#define PD_NOVPTACT                    -305774
#define PD_NOVPD                       -305776
#define PD_NOVPDACT                    -305778
#define PD_NOOBL                       -305780
#define PD_NOOBLACT                    -305782
#define PD_NONTD                       -305784
#define PD_NONTDACT                    -305786
#define PD_NOCCL                       -305788
#define PD_NOCCLACT                    -305790
#define PD_NOCCM                       -305792
#define PD_NOCCMACT                    -305794
#define PD_NOSRU                       -305796
#define PD_NOSRUACT                    -305798
#define PD_NOTRT                       -305800
#define PD_NOTRTACT                    -305802
#define PD_NOLIT                       -305804
#define PD_NOLITACT                    -305806
#define PD_NOSNS                       -305808
#define PD_NOSNSACT                    -305810
#define PD_NOTZO                       -305812
#define PD_NOTZOACT                    -305814
#define PD_NOVMS                       -305816
#define PD_NOVMSACT                    -305818
#define PD_NOVOL                       -305820
#define PD_NOVOLACT                    -305822
#define PD_NOINF                       -305824
#define PD_NOINFACT                    -305826
#define PD_NOADC                       -305828
#define PD_NOADCACT                    -305830
#define PD_NOFTB                       -305832
#define PD_NOFTBACT                    -305834
#define PD_NOFRO                       -305836
#define PD_NOFROACT                    -305838
#define PD_NOQUA                       -305840
#define PD_NOQUAACT                    -305842
#define PD_NOOTHQUA                    -305844
#define PD_NOOTHQUAACT                 -305846
#define PD_NOBAS                       -305848
#define PD_NOBASACT                    -305850
#define PD_NOOTHBAS                    -305852
#define PD_NOOTHBASACT                 -305854
#define PD_NOFLT                       -305856
#define PD_NOFLTACT                    -305858
#define PD_NOAFT                       -305860
#define PD_NOAFTACT                    -305862
#define PD_NOPFT                       -305864
#define PD_NOPFTACT                    -305866
#define PD_NOPEV                       -305868
#define PD_NOPEVACT                    -305870
#define PD_NOPOD                       -305872
#define PD_NOPODACT                    -305874
#define PD_NOPRY                       -305876
#define PD_NOPRYACT                    -305878
#define PD_NOEXT                       -305880
#define PD_NOEXTACT                    -305882
#define PD_NOTAX                       -305884
#define PD_NOTAXACT                    -305886
#define PD_NOBNK                       -305888
#define PD_NOBNKACT                    -305890
#define PD_NOCSS                       -305892
#define PD_NOCSSACT                    -305894
#define PD_NOCSB                       -305896
#define PD_NOCSBACT                    -305898
#define PD_NOTRA                       -305900
#define PD_NOTRAACT                    -305902
#define PD_NOPRD                       -305904
#define PD_NOPRDACT                    -305906
#define PD_NOFRT                       -305908
#define PD_NOFRTACT                    -305910
#define PD_NOWHN                       -305912
#define PD_NOWHNACT                    -305914
#define PD_NOSYM                       -305916
#define PD_NOSYMACT                    -305918
#define PD_NOSBS                       -305920
#define PD_NOSBSACT                    -305922
#define PD_NODLVINT                    -305924
#define PD_NODLVINTACT                 -305926
#define PD_NOWIN                       -305928
#define PD_NOWINACT                    -305930
#define PD_NOPUR                       -305932
#define PD_NOPURACT                    -305934
#define PD_NOBBO                       -305936
#define PD_NOBBOACT                    -305938
#define PD_NOCRS                       -305940
#define PD_NOCRSACT                    -305942
#define PD_NOTRC                       -305944
#define PD_NOTRCACT                    -305946
#define PD_NOTRR                       -305948
#define PD_NOTRRACT                    -305950
#define PD_NOSPR                       -305952
#define PD_NOSPRACT                    -305954
#define PD_NOPSR                       -305956
#define PD_NOPSRACT                    -305958
#define PD_NOBASINS                    -305960
#define PD_NOBASINSACT                 -305962
#define PD_NOOTHINS                    -305964
#define PD_NOOTHINSACT                 -305966
#define PD_NOFATY                      -305968
#define PD_NOFATYACT                   -305970
#define PD_NOWCC                       -305972
#define PD_NOWCCACT                    -305974
#define PD_NOLVMS                      -305976
#define PD_NOLVMSACT                   -305978
#define PD_NOHVMS                      -305980
#define PD_NOHVMSACT                   -305982
#define PD_NORNT                       -305984
#define PD_NOCHGORD                    -305986
#define PD_NOFRMMNU                    -305988
#define PD_NOFRMMNUACT                 -305990
#define PD_NOLFA                       -305992
#define PD_NOLFAACT                    -305994
#define PD_NOLNO                       -305996
#define PD_NOLNOACT                    -305998
#define PD_NONOD                       -306000
#define PD_NONODACT                    -306002
#define PD_NOSRI                       -306004
#define PD_NOSRIACT                    -306006
#define PD_NOTDS                       -306008
#define PD_NOTDSACT                    -306010
#define PD_NOTDP                       -306012
#define PD_NOTDPACT                    -306014
#define PD_INVULTIMO                   -306016
#define PD_INVALWCREATE                -306018
#define PD_INVCALCLTDNOT               -306020
#define PD_INVCALCSTARTNOT             -306022
#define PD_INVCALCSTOPSTART            -306024
#define PD_INVCALCEXPSTOP              -306026
#define PD_EXPMOVBACK                  -306028
#define PD_EXPMOVFORW                  -306030
#define PD_LTDMOVBACK                  -306032
#define PD_LTDMOVFORW                  -306034
#define PD_LTDNOTMOVBACK               -306036
#define PD_SETTLMOVBACK                -306038
#define PD_SETTLMOVFORW                -306040
#define PD_NOTMOVBACK                  -306042
#define PD_NOTMOVFORW                  -306044
#define PD_DLVSTARTMOVBACK             -306046
#define PD_DLVSTARTMOVFORW             -306048
#define PD_DLVSTOPMOVBACK              -306050
#define PD_DLVSTOPMOVFORW              -306052
#define PD_STARTMOVBACK                -306054
#define PD_STARTMOVFORW                -306056
#define PD_STARTNOTMOVBACK             -306058
#define PD_STOPMOVBACK                 -306060
#define PD_STOPMOVFORW                 -306062
#define PD_NOOPN                       -306064
#define PD_NOOPNACT                    -306066
#define PD_NOCOP                       -306068
#define PD_NOCOPACT                    -306070
#define PD_OPENONMAR                   -306072
#define PD_COPNOTEMPTY                 -306074
#define PD_COPPRICEEMPTY               -306076
#define PD_NOPMMCST                    -306078
#define PD_NOPMMCSTACT                 -306080
#define PD_NOPRMEXC                    -306082
#define PD_NOPRMEXCACT                 -306084
#define PD_NOCOG                       -306086
#define PD_NOCOGACT                    -306088
#define PD_NOFML                       -306090
#define PD_NOFMLACT                    -306092
#define PD_NOFOV                       -306094
#define PD_NOFOVACT                    -306096
#define PD_NOOBK                       -306098
#define PD_NOOBKACT                    -306100
#define PD_NOPDP                       -306102
#define PD_NOPDPACT                    -306104
#define PD_NOSYI                       -306106
#define PD_NOSYIACT                    -306108
#define PD_NOTSR                       -306110
#define PD_NOTSRACT                    -306112
#define PD_NOEDG                       -306114
#define PD_NOEDGACT                    -306116
#define PD_NOSPG                       -306118
#define PD_NOSPGACT                    -306120
#define PD_NOLRE                       -306122
#define PD_NOLREACT                    -306124
#define PD_NOLCO                       -306126
#define PD_NOLCOACT                    -306128
#define PD_ACCASPAYEMPTY               -306130
#define PD_ACCBDXDEALEMPTY             -306132
#define PD_ACCCHKLEGEMPTY              -306134
#define PD_ACCESSTYPEEMPTY             -306136
#define PD_ACCIDEMPTY                  -306138
#define PD_ACCMAXLEGEMPTY              -306140
#define PD_ACCMINQEMPTY                -306142
#define PD_ACCNOEMPTY                  -306144
#define PD_ACCPUBINFEMPTY              -306146
#define PD_ACCSPRCHKEMPTY              -306148
#define PD_ACREMPTY                    -306150
#define PD_ACRACCIDEMPTY               -306152
#define PD_ACTFROMEMPTY                -306154
#define PD_ACTIVEEMPTY                 -306156
#define PD_ACTPASSEMPTY                -306158
#define PD_ADCIDEMPTY                  -306160
#define PD_AFTIDEMPTY                  -306162
#define PD_ATYIDEMPTY                  -306164
#define PD_ALARMEMPTY                  -306166
#define PD_APPLEVENTEMPTY              -306168
#define PD_BASEDONEMPTY                -306170
#define PD_BBOIDEMPTY                  -306172
#define PD_BESTPREMPTY                 -306174
#define PD_BLOCKEMPTY                  -306176
#define PD_BNKACCEMPTY                 -306178
#define PD_BNKIDEMPTY                  -306180
#define PD_BSSIDEMPTY                  -306182
#define PD_BUYSELLEMPTY                -306184
#define PD_CBAIDEMPTY                  -306186
#define PD_CBCIDEMPTY                  -306188
#define PD_CBGCODEEMPTY                -306190
#define PD_CBGIDEMPTY                  -306192
#define PD_CBRIDEMPTY                  -306194
#define PD_CBTIDEMPTY                  -306196
#define PD_CCLIDEMPTY                  -306198
#define PD_CCLUNITEMPTY                -306200
#define PD_CCMIDEMPTY                  -306202
#define PD_CHGIDEMPTY                  -306204
#define PD_CISIDEMPTY                  -306206
#define PD_CHAIDEMPTY                  -306208
#define PD_CLASSEMPTY                  -306210
#define PD_CLEAREDEMPTY                -306212
#define PD_CLEXPEMPTY                  -306214
#define PD_CLHIDEMPTY                  -306216
#define PD_CLOSALLWEMPTY               -306218
#define PD_CLOSESTSEMPTY               -306220
#define PD_COMIDEMPTY                  -306222
#define PD_COMBILLEMPTY                -306224
#define PD_CONTRSZEMPTY                -306226
#define PD_CONTROPEMPTY                -306228
#define PD_CONTRSHREMPTY               -306230
#define PD_CONTRSIZOPEMPTY             -306232
#define PD_CONVDATEEMPTY               -306234
#define PD_COUIDEMPTY                  -306236
#define PD_COUPONEMPTY                 -306238
#define PD_CROSSPREMPTY                -306240
#define PD_CRSIDEMPTY                  -306242
#define PD_CSBIDEMPTY                  -306244
#define PD_CSSIDEMPTY                  -306246
#define PD_CSTIDEMPTY                  -306248
#define PD_CURIDEMPTY                  -306250
#define PD_CUSTCODEEMPTY               -306252
#define PD_DAILYMTHEMPTY               -306254
#define PD_DATEEMPTY                   -306256
#define PD_DAYSEMPTY                   -306258
#define PD_DEALOPEMPTY                 -306260
#define PD_DEFACCEMPTY                 -306262
#define PD_DEFPOSEMPTY                 -306264
#define PD_DELIVEMPTY                  -306266
#define PD_DELIVINSEMPTY               -306268
#define PD_DELNTDEMPTY                 -306270
#define PD_DERIVEMPTY                  -306272
#define PD_DLSCBAIDEMPTY               -306274
#define PD_DLSDATEEMPTY                -306276
#define PD_DLVINTIDEMPTY               -306278
#define PD_DLVLISTEMPTY                -306280
#define PD_DLVSTARTNTDEMPTY            -306282
#define PD_DLVSTOPNTDEMPTY             -306284
#define PD_EVNOEMPTY                   -306286
#define PD_EXCCODEEMPTY                -306288
#define PD_EXCIDEMPTY                  -306290
#define PD_EXCLEMPTY                   -306292
#define PD_EXPFREQEMPTY                -306294
#define PD_EXPDATEEMPTY                -306296
#define PD_EXPIDEMPTY                  -306298
#define PD_EXPNTDEMPTY                 -306300
#define PD_EXPPERIODEMPTY              -306302
#define PD_FACILITYEMPTY               -306304
#define PD_FACTYPEMPTY                 -306306
#define PD_FASTMARCREMPTY              -306308
#define PD_FASTMARTIMEEMPTY            -306310
#define PD_FIELDCEMPTY                 -306312
#define PD_FILLKILLEMPTY               -306314
#define PD_FIRMEMPTY                   -306316
#define PD_FLTIDEMPTY                  -306318
#define PD_FROMEMPTY                   -306320
#define PD_FROMMENUEMPTY               -306322
#define PD_FTBIDEMPTY                  -306324
#define PD_GENSEREMPTY                 -306326
#define PD_GROUPSETTLEMPTY             -306328
#define PD_INCIDEMPTY                  -306330
#define PD_INDEXEMPTY                  -306332
#define PD_INFALWDEMPTY                -306334
#define PD_INGIDEMPTY                  -306336
#define PD_INSIDEMPTY                  -306338
#define PD_INTBDXDEALEMPTY             -306340
#define PD_INTCHKLEGEMPTY              -306342
#define PD_INTERPEMPTY                 -306344
#define PD_INTERPREMPTY                -306346
#define PD_INTIDEMPTY                  -306348
#define PD_INTMAXLEGEMPTY              -306350
#define PD_INTNOTTRADED                -306352
#define PD_INTSPRCHKEMPTY              -306354
#define PD_IPADDREMPTY                 -306356
#define PD_ISINASSEMPTY                -306358
#define PD_ISAPIEMPTY                  -306360
#define PD_ISCLOSEEMPTY                -306362
#define PD_ISFRACTIONSEMPTY            -306364
#define PD_ISEXCLEMPTY                 -306366
#define PD_ISMMEMPTY                   -306368
#define PD_ISNIDEMPTY                  -306370
#define PD_ISNLOWEMPTY                 -306372
#define PD_ISNHIGHEMPTY                -306374
#define PD_ISNETEMPTY                  -306376
#define PD_ISOIEMPTY                   -306378
#define PD_ISOPENEMPTY                 -306380
#define PD_ISSDATEEMPTY                -306382
#define PD_ISSUEMARKEMPTY              -306384
#define PD_ISTRADEREMPTY               -306386
#define PD_ISTRANSEMPTY                -306388
#define PD_ISTRTRDEVTEMPTY             -306390
#define PD_LANIDEMPTY                  -306392
#define PD_LEGNOEMPTY                  -306394
#define PD_LFAIDEMPTY                  -306396
#define PD_LNOIDEMPTY                  -306398
#define PD_LIFETIMEEMPTY               -306400
#define PD_LITIDEMPTY                  -306402
#define PD_LOWLSTEMPTY                 -306404
#define PD_LSTIDEMPTY                  -306406
#define PD_LTRNTDEMPTY                 -306408
#define PD_MANDPREMPTY                 -306410
#define PD_MANDVOLEMPTY                -306412
#define PD_MARIDEMPTY                  -306414
#define PD_MAXCOMBOLEGEMPTY            -306416
#define PD_MAXTIMEEMPTY                -306418
#define PD_MAXUNITEMPTY                -306420
#define PD_MAXVOLEMPTY                 -306422
#define PD_MAXWAITEMPTY                -306424
#define PD_MEMTYPEMPTY                 -306426
#define PD_MENUEMPTY                   -306428
#define PD_MENUTYPEEMPTY               -306430
#define PD_MENUNOEMPTY                 -306432
#define PD_MINHOLDEMPTY                -306434
#define PD_MINQEMPTY                   -306436
#define PD_MINTIMEEMPTY                -306438
#define PD_MINUNITEMPTY                -306440
#define PD_MINVOLEMPTY                 -306442
#define PD_MINWAITEMPTY                -306444
#define PD_MONTHCODEEMPTY              -306446
#define PD_MONTHNAMEEMPTY              -306448
#define PD_MONTHNOEMPTY                -306450
#define PD_MPORCLEMPTY                 -306452
#define PD_NAMEEMPTY                   -306454
#define PD_NEARESTEMPTY                -306456
#define PD_NEWINSEMPTY                 -306458
#define PD_NOCYCLEMPTY                 -306460
#define PD_NODENAMEEMPTY               -306462
#define PD_NODENUMEMPTY                -306464
#define PD_NOOFDLVEMPTY                -306466
#define PD_NOOFINITEMPTY               -306468
#define PD_NOOFLEGSEMPTY               -306470
#define PD_NOSERIESEMPTY               -306472
#define PD_NOTNTDEMPTY                 -306474
#define PD_NOTPERIODEMPTY              -306476
#define PD_NTDIDEMPTY                  -306478
#define PD_OBLIDEMPTY                  -306480
#define PD_OBLRIGHTSEMPTY              -306482
#define PD_OLDINSEMPTY                 -306484
#define PD_ORDNOEMPTY                  -306486
#define PD_OPENCLOSEEMPTY              -306488
#define PD_OPENSTSEMPTY                -306490
#define PD_OPIFBUYEMPTY                -306492
#define PD_OPIFSELLEMPTY               -306494
#define PD_ORDEREMPTY                  -306496
#define PD_ORGIDEMPTY                  -306498
#define PD_OVRBIDEMPTY                 -306500
#define PD_PASSWORDEMPTY               -306502
#define PD_PAYTYPEEMPTY                -306504
#define PD_PEVIDEMPTY                  -306506
#define PD_PFTIDEMPTY                  -306508
#define PD_PHYSADDREMPTY               -306510
#define PD_PODIDEMPTY                  -306512
#define PD_POSTYPEMPTY                 -306514
#define PD_PRDDATEEMPTY                -306516
#define PD_PRDEVEMPTY                  -306518
#define PD_PRDIDEMPTY                  -306520
#define PD_PRDOMNETEMPTY               -306522
#define PD_PRDVENDOREMPTY              -306524
#define PD_PREMUNITEMPTY               -306526
#define PD_PRICEUNITEMPTY              -306528
#define PD_PRICEQEMPTY                 -306530
#define PD_PRICBAIDEMPTY               -306532
#define PD_PRIDAYSEMPTY                -306534
#define PD_PRIMMARKEMPTY               -306536
#define PD_PRINOTEMPTY                 -306538
#define PD_PRIUNITEMPTY                -306540
#define PD_PROPEMPTY                   -306542
#define PD_PSRIDEMPTY                  -306544
#define PD_PUBIDEMPTY                  -306546
#define PD_PURIDEMPTY                  -306548
#define PD_QREQBDXEMPTY                -306550
#define PD_RACCESSEMPTY                -306552
#define PD_WACCESSEMPTY                -306554
#define PD_RATIOEMPTY                  -306556
#define PD_REALTIMEEMPTY               -306558
#define PD_REFNTDEMPTY                 -306560
#define PD_REJACCEMPTY                 -306562
#define PD_REJTIMOUTEMPTY              -306564
#define PD_RESPEMPTY                   -306566
#define PD_RISKEMPTY                   -306568
#define PD_RNTEMPTY                    -306570
#define PD_SBSIDEMPTY                  -306572
#define PD_SBSSTATUSEMPTY              -306574
#define PD_SECCBAIDEMPTY               -306576
#define PD_SECDAYSEMPTY                -306578
#define PD_SEGMNOEMPTY                 -306580
#define PD_SETTLDAYSEMPTY              -306582
#define PD_SIZEEMPTY                   -306584
#define PD_SHORTNAMEEMPTY              -306586
#define PD_SOSTRKPROPEMPTY             -306588
#define PD_SOSTRKPRFACEMPTY            -306590
#define PD_SOCONTRSZOPEMPTY            -306592
#define PD_SOCONTRSZFACEMPTY           -306594
#define PD_SODEALPROPEMPTY             -306596
#define PD_SODEALPRFACEMPTY            -306598
#define PD_SNSIDEMPTY                  -306600
#define PD_SNSUNDEREMPTY               -306602
#define PD_SNSNOOFDECEMPTY             -306604
#define PD_SNSDECEMPTY                 -306606
#define PD_SNSISSID1EMPTY              -306608
#define PD_SNSISSCODEEMPTY             -306610
#define PD_SNSSIGNEMPTY                -306612
#define PD_SNSSIGNCODEEMPTY            -306614
#define PD_SPREADEMPTY                 -306616
#define PD_SPRIDEMPTY                  -306618
#define PD_SPSIDEMPTY                  -306620
#define PD_SRUIDEMPTY                  -306622
#define PD_SRUONEHIGH                  -306624
#define PD_SRUONELOW                   -306626
#define PD_SRUDTIMENOTEMPTY            -306628
#define PD_STARTPROCEMPTY              -306630
#define PD_STATUSEMPTY                 -306632
#define PD_STEPEMPTY                   -306634
#define PD_STEPSFROMUNDEMPTY           -306636
#define PD_STEPSINCYCEMPTY             -306638
#define PD_STOPTIMEEMPTY               -306640
#define PD_STOPTYPEEMPTY               -306642
#define PD_STIMULIEMPTY                -306644
#define PD_STLNTDEMPTY                 -306646
#define PD_STRIKECODEEMPTY             -306648
#define PD_STREXISTEMPTY               -306650
#define PD_STROPEMPTY                  -306652
#define PD_STRUNITEMPTY                -306654
#define PD_SUBSYSEMPTY                 -306656
#define PD_SYMIDEMPTY                  -306658
#define PD_TAXIDEMPTY                  -306660
#define PD_TIMEUNITEMPTY               -306662
#define PD_TIMEBTWTRADEEMPTY           -306664
#define PD_TOEMPTY                     -306666
#define PD_TRADDATEEMPTY               -306668
#define PD_TRADDAYSEMPTY               -306670
#define PD_TRADEDEMPTY                 -306672
#define PD_TRADTIMEEMPTY               -306674
#define PD_TRADTYPEMPTY                -306676
#define PD_TRCIDEMPTY                  -306678
#define PD_TRDREPRULEEMPTY             -306680
#define PD_TRRIDEMPTY                  -306682
#define PD_TRTIDEMPTY                  -306684
#define PD_TSSIDEMPTY                  -306686
#define PD_TZOIDEMPTY                  -306688
#define PD_TYPEEMPTY                   -306690
#define PD_ULTIMO1EMPTY                -306692
#define PD_ULTIMO2EMPTY                -306694
#define PD_USEMODDUPLEMPTY             -306696
#define PD_CALCLTDNOTEMPTY             -306698
#define PD_CALCSTARTNOTEMPTY           -306700
#define PD_CALCSTOPSTARTEMPTY          -306702
#define PD_CALCEXPSTOPEMPTY            -306704
#define PD_UNDOPEMPTY                  -306706
#define PD_UPPIDEMPTY                  -306708
#define PD_UPPINTIDEMPTY               -306710
#define PD_USRIDEMPTY                  -306712
#define PD_USTIDEMPTY                  -306714
#define PD_VALIDLASTEMPTY              -306716
#define PD_VPDIDEMPTY                  -306718
#define PD_XAXISEMPTY                  -306720
#define PD_YAXISEMPTY                  -306722
#define PD_VOLIDEMPTY                  -306724
#define PD_WCCIDEMPTY                  -306726
#define PD_WHENEMPTY                   -306728
#define PD_WINIDEMPTY                  -306730
#define PD_DESCEMPTY                   -306732
#define PD_MSTCLHIDEMPTY               -306734
#define PD_BASCURIDEMPTY               -306736
#define PD_EXTIDEMPTY                  -306738
#define PD_EXTIDNOTEMPTY               -306740
#define PD_MAXSPANEMPTY                -306742
#define PD_PONESPREMPTY                -306744
#define PD_PSECSPREMPTY                -306746
#define PD_PREGEMPTY                   -306748
#define PD_PALLEMPTY                   -306750
#define PD_HVSTPEMPTY                  -306752
#define PD_WVSTPEMPTY                  -306754
#define PD_FLRTSTPEMPTY                -306756
#define PD_PCDAYEMPTY                  -306758
#define PD_ERTRDEMPTY                  -306760
#define PD_SWTRDEMPTY                  -306762
#define PD_FIXBCEMPTY                  -306764
#define PD_PRIMPBEMPTY                 -306766
#define PD_SECPBEMPTY                  -306768
#define PD_CORREMPTY                   -306770
#define PD_ITRHIGHEMPTY                -306772
#define PD_ITRACREMPTY                 -306774
#define PD_ITRMAXEMPTY                 -306776
#define PD_CALCMEMPTY                  -306778
#define PD_PRINTPEMPTY                 -306780
#define PD_BVTIMEMPTY                  -306782
#define PD_HMAXEMPTY                   -306784
#define PD_NEGTIMEMPTY                 -306786
#define PD_VOLUSDEMPTY                 -306788
#define PD_USRNAMEEMPTY                -306790
#define PD_FASTMARKEMPTY               -306792
#define PD_MAXOMNTRTEMPTY              -306794
#define PD_BRDTYPEEMPTY                -306796
#define PD_DISCUNITEMPTY               -306798
#define PD_DISCOUNTEMPTY               -306800
#define PD_PRCALCMEMPTY                -306802
#define PD_DLVSTARTEMPTY               -306804
#define PD_DLVSTOPEMPTY                -306806
#define PD_STARTDATEEMPTY              -306808
#define PD_STOPDATEEMPTY               -306810
#define PD_AUTOEMPTY                   -306812
#define PD_MSUIDEMPTY                  -306814
#define PD_SUPTRPEMPTY                 -306816
#define PD_SUPBPEMPTY                  -306818
#define PD_SUPLTREMPTY                 -306820
#define PD_SUPITREMPTY                 -306822
#define PD_SUPUNCRSEMPTY               -306824
#define PD_PRINFEMPTY                  -306826
#define PD_VOLINFEMPTY                 -306828
#define PD_DELIVMARGEMPTY              -306830
#define PD_PAYMARGEMPTY                -306832
#define PD_USEDIVIDEMPTY               -306834
#define PD_OPENINTEMPTY                -306836
#define PD_ENABLEOPENEMPTY             -306838
#define PD_BESTPROPENEMPTY             -306840
#define PD_OPNIDEMPTY                  -306842
#define PD_OPENTIMEEMPTY               -306844
#define PD_CLOSETIMEEMPTY              -306846
#define PD_COPLESSEMPTY                -306848
#define PD_COPCHGEMPTY                 -306850
#define PD_COPIDEMPTY                  -306852
#define PD_OPENALLSTOPEMPTY            -306854
#define PD_COGCODEEMPTY                -306856
#define PD_COGIDEMPTY                  -306858
#define PD_OBKCODEEMPTY                -306860
#define PD_OBKIDEMPTY                  -306862
#define PD_TSRIDEMPTY                  -306864
#define PD_EDGIDEMPTY                  -306866
#define PD_SPGIDEMPTY                  -306868
#define PD_FMLIDEMPTY                  -306870
#define PD_FOVIDEMPTY                  -306872
#define PD_PDPIDEMPTY                  -306874
#define PD_SYIIDEMPTY                  -306876
#define PD_PRMEXCIDEMPTY               -306878
#define PD_MINBBOEMPTY                 -306880
#define PD_MKTORDEMPTY                 -306882
#define PD_LMTMKTEMPTY                 -306884
#define PD_OPNRECEMPTY                 -306886
#define PD_MAXFML                      -306888
#define PD_SRIIDEMPTY                  -306890
#define PD_BIDNOTASKEMPTY              -306892
#define PD_BIDANDASKEMPTY              -306894
#define PD_ASKNOTBIDEMPTY              -306896
#define PD_ASKANDBIDEMPTY              -306898
#define PD_SPREADFROMEMPTY             -306900
#define PD_MINBIDPRICEEMPTY            -306902
#define PD_MINASKPRICEEMPTY            -306904
#define PD_PRICEEMPTY                  -306906
#define PD_ABSPEREMPTY                 -306908
#define PD_MINSPREADEMPTY              -306910
#define PD_MAXSPREADEMPTY              -306912
#define PD_ROUNDINGEMPTY               -306914
#define PD_TDPIDEMPTY                  -306916
#define PD_TDSIDEMPTY                  -306918
#define PD_DELAYLESSCOP                -306920
#define PD_DOUBLERISKP                 -306922
#define PD_ISSINFUTURE                 -306924
#define PD_LREIDEMPTY                  -306926
#define PD_LCOIDEMPTY                  -306928
#define PD_REGNAMEEMPTY                -306930
#define PD_REFTOACC                    -306932
#define PD_REFTOACR                    -306934
#define PD_REFTOCBC                    -306936
#define PD_REFTOCBS                    -306938
#define PD_REFTOCBT                    -306940
#define PD_REFTOCCL                    -306942
#define PD_REFTOCLH                    -306944
#define PD_REFTOCLI                    -306946
#define PD_REFTOCOM                    -306948
#define PD_REFTOCSL                    -306950
#define PD_REFTOCSS                    -306952
#define PD_REFTOCST                    -306954
#define PD_REFTOCUP                    -306956
#define PD_REFTOEXC                    -306958
#define PD_REFTOFVL                    -306960
#define PD_REFTOICO                    -306962
#define PD_REFTOILU                    -306964
#define PD_REFTOINC                    -306966
#define PD_REFTOINS                    -306968
#define PD_REFTOINT                    -306970
#define PD_REFTOISN                    -306972
#define PD_REFTOISS                    -306974
#define PD_REFTOITU                    -306976
#define PD_REFTOLGP                    -306978
#define PD_REFTOLIT                    -306980
#define PD_REFTOLIU                    -306982
#define PD_REFTOLNO                    -306984
#define PD_REFTOLTT                    -306986
#define PD_REFTOLTU                    -306988
#define PD_REFTOMAC                    -306990
#define PD_REFTOMAR                    -306992
#define PD_REFTOMNA                    -306994
#define PD_REFTOORG                    -306996
#define PD_REFTOPAYCST                 -306998
#define PD_REFTOPEV                    -307000
#define PD_REFTOPFT                    -307002
#define PD_REFTOPQR                    -307004
#define PD_REFTOPUR                    -307006
#define PD_REFTOSYM                    -307008
#define PD_REFTOTAX                    -307010
#define PD_REFTOTRC                    -307012
#define PD_REFTOUSR                    -307014
#define PD_REFTOMNU                    -307016
#define PD_REFTOOBL                    -307018
#define PD_REFTOCOG                    -307020
#define PD_REFTOFML                    -307022
#define PD_REFTOFOV                    -307024
#define PD_REFTOOBK                    -307026
#define PD_REFTOPDP                    -307028
#define PD_REFTOSYI                    -307030
#define PD_REFTOTSR                    -307032
#define PD_REFTOSRI                    -307034
#define PD_REFTOTDS                    -307036
#define PD_REFTOTDP                    -307038
#define PD_REFTOLRE                    -307040
#define PD_REFTOLCO                    -307042
#define PD_SYSERR                      -307044
#define PD_INSFMEM                     -307046
#define PD_ERRNOEXP                    -307048
#define PD_ERRNOMAR                    -307050
#define PD_ERRNOINT                    -307052
#define PD_ERRNOINC                    -307054
#define PD_ERRNOCCL                    -307056
#define PD_FLDTYPENOTEX                -307058
#define PD_FLDNOTEX                    -307060
#define PD_WRONGVERSION                -307062
#define PD_VPCNOINIT                   -307064
#define PD_VPCNOANS                    -307066
#define PD_SCODENOTCREATED             -307068
#define PD_MCODENOTCREATED             -307070
#define PD_WRUPDNOTALLOWED             -307072
#define PD_UPDNOTBOTHSYM               -307074
#define PD_OMDUNOTEVT                  -307076
#define PD_ILLEGFAC                    -307078
#define PD_ILLSETTLPROP                -307080
#define PD_SERISTRADED                 -307082
#define PD_ALLOWUNINTEMPTY             -307084
#define PD_WRONGUNDATTR                -307086
#define PD_WRONGEXPATTR                -307088
#define PD_WRONGDEDATTR                -307090
#define PD_QRYONNNOTSUPP               -307092
#define PD_COMBODEALEMPTY              -307094
#define PD_COUNTSIGNEMPTY              -307096
#define PD_NOCLP                       -307098
#define PD_NOCLPACT                    -307100
#define PD_CLPIDEMPTY                  -307102
#define PD_NETTMTHEMPTY                -307104
#define PD_DIFFCLP                     -307106
#define PD_STEPNOTMULT                 -307108
#define PD_LOWZEROMISS                 -307110
#define PD_ISSNOOPRA                   -307112
#define PD_SONOOPRA                    -307114
#define PD_SOISSOPRAISEQ               -307116
#define PD_SOOPRAISEQ                  -307118
#define PD_ISSOPRAISEQ                 -307120
#define PD_ISSOPRAEXIST                -307122
#define PD_SOOPRAEXIST                 -307124
#define PD_NEWINSIDEXIST               -307126
#define PD_NEWINSCODEEXIST             -307128
#define PD_SOINSIDEXIST                -307130
#define PD_SOINSCODEEXIST              -307132
#define PD_CLPCSSIDEMPTY               -307134
#define PD_MMLCKTIME                   -307136
#define PD_BLKRSPTIME                  -307138
#define PD_BLKMINSIZE                  -307140
#define PD_ISSTYPEEMPTY                -307142
#define PD_NOTALLSPG                   -307144
#define PD_TOOMANYSPG                  -307146
#define PD_DOUBLESPG                   -307148
#define PD_DOUBLEEDG                   -307150
#define PD_SYISYMEXIST                 -307152
#define PD_TYPEISTRADED                -307154
#define PD_CBTEXISTS                   -307156
#define PD_MARNOTTRADED                -307158
#define PD_CLASSISTRADED               -307160
#define PD_IMPLNOTINFUT                -307162
#define PD_INTRADAYNOTALLWD            -307164
#define PD_TOTWCNOTALLWD               -307166
#define PD_CLQRYFAIL                   -307168
#define PD_INFOQRYFAIL                 -307170
#define PD_IDCHANGED                    307171
#define PD_INCCHANGED                   307173
#define PD_EXPCHANGED                   307175
#define PD_LTTCHANGED                   307177
#define PD_STRCHANGED                   307179
#define PD_ISNCHANGED                   307181
#define PD_NORELCHANGED                 307183
#define PD_ISSUELSTONLY                -307184
#define PD_ACTIVELSTONLY               -307186
#define PD_LSTCHGNOTALLOWED            -307188
#define PD_BOTHUNDNOTALLOWED           -307190
#define PD_NEWMARNOTALLOWED            -307192
#define PD_DECISNOTEQ                  -307194
#define PD_TSEIDEMPTY                  -307196
#define PD_TIMEEMPTY                   -307198
#define PD_STATEEMPTY                  -307200
#define PD_DOUBLETIME                  -307202
#define PD_NOTSE                       -307204
#define PD_NOTSEACT                    -307206
#define PD_CSTATEWR                    -307208
#define PD_PSTATEWR                    -307210
#define PD_ASTATEWR                    -307212
#define PD_RSTATEWR                    -307214
#define PD_ILLSTARTPROC                -307216
#define PD_STARTINTOVR                 -307218
#define PD_LTTIDEMPTY                  -307220
#define PD_NOLTT                       -307222
#define PD_NOLTTACT                    -307224
#define PD_VALIDFROMEMPTY              -307226
#define PD_VALIDUNTILEMPTY             -307228
#define PD_SOMODEMPTY                  -307230
#define PD_NOINSTEMPLFOUND             -307232
#define PD_NOINCTEMPLFOUND             -307234
#define PD_NOTMCOMFOUND                -307236
#define PD_BOTHNEWSPEMPTY              -307238
#define PD_TSEDIFFNTD                  -307240
#define PD_ONETEMPALLWD                -307242
#define PD_CALCLTDEXPEMPTY             -307244
#define PD_INVLTDCORR                  -307246
#define PD_OPRAINDEXEMPTY              -307248
#define PD_DOUBLEEXC                   -307250
#define PD_ACTCRSEMPTY                 -307252
#define PD_SSTIDEMPTY                  -307254
#define PD_VOLINTEMPTY                 -307256
#define PD_AGGRPAYEMPTY                -307258
#define PD_RESERVSTATE                 -307260
#define PD_HALFDAYEMPTY                -307262
#define PD_NOSST                       -307264
#define PD_NOSSTACT                    -307266
#define PD_CNTRSZISNOTEQ               -307268
#define PD_WREXPOP                     -307270
#define PD_WREXPFAC                    -307272
#define PD_REFTOSBS                    -307274
#define PD_SWBIDEMPTY                  -307276
#define PD_REFINSEMPTY                 -307278
#define PD_LOCKREFEMPTY                -307280
#define PD_DOUBLESWB                   -307282
#define PD_NOREFINS                    -307284
#define PD_NOREFINSACT                 -307286
#define PD_NOSWB                       -307288
#define PD_SWBALRSUSP                  -307290
#define PD_SWBALRRESUMED               -307292
#define PD_NOTLOCKED                   -307294
#define PD_CEGIDEMPTY                  -307296
#define PD_DOUBLECEG                   -307298
#define PD_MATURITYEMPTY               -307300
#define PD_FCOUPONEMPTY                -307302
#define PD_CUPFREQEMPTY                -307304
#define PD_NOOUTRREFINS                -307306
#define PD_NOOUTRREFINSACT             -307308
#define PD_NOOUTRINS                   -307310
#define PD_NOOUTRINSACT                -307312
#define PD_OUTRREFINSEMPTY             -307314
#define PD_OUTRINSEMPTY                -307316
#define PD_IPRIDEMPTY                  -307318
#define PD_NOIPR                       -307320
#define PD_NOIPRACT                    -307322
#define PD_NOREFSPEC                   -307324
#define PD_REFSPEC                     -307326
#define PD_DIFFREFSPEC                 -307328
#define PD_NOTSUSPENDED                -307330
#define PD_REFMUSTBESWAP               -307332
#define PD_REFISSWAP                   -307334
#define PD_OUTRREFISSWAP               -307336
#define PD_LEGMUSTBESWAP               -307338
#define PD_OUTRLEGISSWAP               -307340
#define PD_LEGEQREF                    -307342
#define PD_OLEGEQREF                   -307344
#define PD_OLEGEQOREF                  -307346
#define PD_DOUBLEOSWB                  -307348
#define PD_DOUBLEGNO                   -307350
#define PD_PRYTYPEEMPTY                -307352
#define PD_PRYCONVEMPTY                -307354
#define PD_USECUSIPEMPTY               -307356
#define PD_WRONGCUSIP                  -307358
#define PD_OBLEVNOT1OR5                -307360
#define PD_CUSIPTOLONG                 -307362
#define PD_WRLTTTIME                   -307364
#define PD_REFEXISTASREF               -307366
#define PD_LEGEXISTASREF               -307368
#define PD_REFEXISTASLEG               -307370
#define PD_LEGEXISTASLEG               -307372
#define PD_ERRINFRAC                   -307374
#define PD_REFTOSWB                    -307376
#define PD_MARORDACTWRONG              -307378
#define PD_MARORDACTNOTDEF             -307380
#define PD_COUPAFTMAT                  -307382
#define PD_SERIESEXCEED                -307384
#define PD_LOCKEDSWAP                  -307386
#define PD_SWAPNOTINBOX                -307388
#define PD_DESIDEMPTY                  -307390
#define PD_REFTODES                    -307392
#define PD_DGRIDEMPTY                  -307394
#define PD_REFTODGR                    -307396
#define PD_UPPEREMPTY                  -307398
#define PD_VOLCHGEMPTY                 -307400
#define PD_VDSIDEMPTY                  -307402
#define PD_PMMOBLTYPEEMPTY             -307404
#define PD_TRDIDEMPTY                  -307406
#define PD_INFFEEDIDEMPTY              -307408
#define PD_DEPOSIDEMPTY                -307410
#define PD_HEDGEEXCIDEMPTY             -307412
#define PD_HEDGECSTIDEMPTY             -307414
#define PD_DOUBLEEXTID                 -307416
#define PD_NODES                       -307418
#define PD_NODESACT                    -307420
#define PD_NOVDS                       -307422
#define PD_NOVDSACT                    -307424
#define PD_NODHB                       -307426
#define PD_NODHBACT                    -307428
#define PD_DHBIDEMPTY                  -307430
#define PD_DEPOSTYPEEMPTY              -307432
#define PD_DECISDIFF                   -307434
#define PD_NODGR                       -307436
#define PD_ISINMISSING                  307437
#define PD_ALRSIGNALLED                -307438
#define PD_REFTOTSE                    -307440
#define PD_NOORV                       -307442
#define PD_NOORVACT                    -307444
#define PD_ORVIDEMPTY                  -307446
#define PD_HEDGEALGEMPTY               -307448
#define PD_NOMTH                       -307450
#define PD_NOMTHACT                    -307452
#define PD_MTHIDEMPTY                  -307454
#define PD_NOPDR                       -307456
#define PD_NOPDRACT                    -307458
#define PD_PDRIDEMPTY                  -307460
#define PD_BOTHCOMCIS                  -307462
#define PD_DOUBLECIS                   -307464
#define PD_NOATR                       -307466
#define PD_NOATRACT                    -307468
#define PD_NOLAI                       -307470
#define PD_NOLAIACT                    -307472
#define PD_NOPRL                       -307474
#define PD_NOPRLACT                    -307476
#define PD_NOCIB                       -307478
#define PD_NOCIBACT                    -307480
#define PD_NOTIR                       -307482
#define PD_NOTIRACT                    -307484
#define PD_NOIMS                       -307486
#define PD_NOIMSACT                    -307488
#define PD_NOICS                       -307490
#define PD_NOICSACT                    -307492
#define PD_ATRIDEMPTY                  -307494
#define PD_AATIDEMPTY                  -307496
#define PD_DOUBLEAAT                   -307498
#define PD_NOAAT                       -307500
#define PD_NOAATACT                    -307502
#define PD_PRFORMEMPTY                 -307504
#define PD_STRFORMEMPTY                -307506
#define PD_CABFORMEMPTY                -307508
#define PD_SETTLUNITEMPTY              -307510
#define PD_CIBIDEMPTY                  -307512
#define PD_ICSIDEMPTY                  -307514
#define PD_IMSIDEMPTY                  -307516
#define PD_PRIOEMPTY                   -307518
#define PD_CRRATEEMPTY                 -307520
#define PD_DSRATIOEMPTY                -307522
#define PD_AORBEMPTY                   -307524
#define PD_CHARGEEMPTY                 -307526
#define PD_LAIIDEMPTY                  -307528
#define PD_REFTOLAI                    -307530
#define PD_MORETHANONE                 -307532
#define PD_DOUBLEINST                  -307534
#define PD_TIERIDEMPTY                 -307536
#define PD_EXPNOEMPTY                  -307538
#define PD_DOUBLETIER                  -307540
#define PD_TIEREMPTY                   -307542
#define PD_DOUBLEICS                   -307544
#define PD_DOUBLEIMS                   -307546
#define PD_PRLIDEMPTY                  -307548
#define PD_EXTPROVEMPTY                -307550
#define PD_EXTERNIDEMPTY               -307552
#define PD_LTUNITEMPTY                 -307554
#define PD_INTRATEEMPTY                -307556
#define PD_EXPISSPEC                   -307558
#define PD_EXPNOTSPEC                  -307560
#define PD_DOUBLETDP                   -307562
#define PD_DOUBLETDS                   -307564
#define PD_INTTRDREPRULEEMPTY          -307566
#define PD_NOMTM                       -307568
#define PD_NOMTMACT                    -307570
#define PD_ATTRRULEEMPTY               -307572
#define PD_ONLYONEDEFSAX               -307574
#define PD_WRONGDATEFORMAT             -307576
#define PD_NOSID                       -307578
#define PD_NOSIDACT                    -307580
#define PD_SIDIDEMPTY                  -307582
#define PD_CURRFORMEMPTY               -307584
#define PD_REFTOATY                    -307586
#define PD_REFTOWIN                    -307588
#define PD_EXCEEDFORMAT                -307590
#define PD_EXCEEDPRFORMAT              -307592
#define PD_EXCEEDCABFORMAT             -307594
#define PD_COMBOMTHEMPTY               -307596
#define PD_WRONGSTRFORMAT              -307598
#define PD_CBOMINLEGSEXCEED            -307600
#define PD_RFQPRICEMPTY                -307602
#define PD_CLOSINGTRDPREMPTY           -307604
#define PD_STRIKEEXCEEDED              -307606
#define PD_FIXINSIDEMPTY               -307608
#define PD_FIXINSIDNOTEMPTY            -307610
#define PD_MMRESPTYPEEMPTY             -307612
#define PD_TRDAUTHEMPTY                -307614
#define PD_NOLEGSDEFINED               -307616
#define PD_NORRU                       -307618
#define PD_NORRUACT                    -307620
#define PD_NOGMS                       -307622
#define PD_NOGMSACT                    -307624
#define PD_NOGCT                       -307626
#define PD_NOGCTACT                    -307628
#define PD_GCTIDEMPTY                  -307630
#define PD_MAXYEMPTY                   -307632
#define PD_FBBIDEMPTY                  -307634
#define PD_FUTINSEMPTY                 -307636
#define PD_REFTOFBB                    -307638
#define PD_FUTMUSTBEFB                 -307640
#define PD_LEGMUSTBEFBLEG              -307642
#define PD_LEGEQFUT                    -307644
#define PD_OUTRLEGISWRONG              -307646
#define PD_OLEGEQFB                    -307648
#define PD_SEVCHFOUND                  -307650
#define PD_NOCONVPRICE                 -307652
#define PD_DOUBLEFBB                   -307654
#define PD_DOUBLEOFBB                  -307656
#define PD_NOCHFOUND                   -307658
#define PD_DIFFCTDSPEC                 -307660
#define PD_DIFFCONVSPEC                -307662
#define PD_FBEXISTASFB                 -307664
#define PD_LEGEXISTASFB                -307666
#define PD_FBEXISTASLEG                -307668
#define PD_NOFBB                       -307670
#define PD_NOCONVFACTOR                -307672
#define PD_REFTOGCG                    -307674
#define PD_DOUBLEGCT                   -307676
#define PD_GMSIDEMPTY                  -307678
#define PD_DOUBLENOMTR                 -307680
#define PD_RRUIDEMPTY                  -307682
#define PD_HIDDVOLMETHEMPTY            -307684
#define PD_DOUBLERRU                   -307686
#define PD_MORPEMPTY                   -307688
#define PD_MORPSPEC                    -307690
#define PD_STARTDATESPEC               -307692
#define PD_STOPDATESPEC                -307694
#define PD_REPOGENSPEC                 -307696
#define PD_RRUIDSPEC                   -307698
#define PD_GMSIDSPEC                   -307700
#define PD_UNDERLEXIST                 -307702
#define PD_SERIESEXIST                 -307704
#define PD_CLASSEXIST                  -307706
#define PD_DUPLUNDERL                  -307708
#define PD_DUPLSERIES                  -307710
#define PD_DUPLISIN                    -307712
#define PD_NOTMPLINC                   -307714
#define PD_NOTMPLCOM                   -307716
#define PD_NOTMPLINS                   -307718
#define PD_ISSDATEWRONG                -307720
#define PD_MATURDATEWRONG              -307722
#define PD_DATEDDATEWRONG              -307724
#define PD_MATURDATEEMPTY              -307726
#define PD_DATEDDATEEMPTY              -307728
#define PD_FIRSTCOUPWRONG              -307730
#define PD_LASTCOUPWRONG               -307732
#define PD_FIRSTCOUPEMPTY              -307734
#define PD_COUPFREQEMPTY               -307736
#define PD_GCGROUPEMPTY                -307738
#define PD_FITWRONG                    -307740
#define PD_NOMINALISZERO               -307742
#define PD_REDEMPISZERO                -307744
#define PD_WRONGDCR                    -307746
#define PD_NOCTDPRICE                  -307748
#define PD_CTDPRICESPEC                -307750
#define PD_PSPIDEMPTY                  -307752
#define PD_NOPSP                       -307754
#define PD_NOPSPACT                    -307756
#define PD_DEFCOLLIDEMPTY              -307758
#define PD_NODEF                       -307760
#define PD_NODEFACT                    -307762
#define PD_REFTOCDC                    -307764
#define PD_REFTOPSP                    -307766
#define PD_DOUBLEDEF                   -307768
#define PD_WRONGDEF                    -307770
#define PD_NODEFSPEC                   -307772
#define PD_FUTBNOTINBOX                -307774
#define PD_INSLONGALREXIST             -307776
#define PD_CBSLONGALREXIST             -307778
#define PD_STARTTERMEMPTY              -307780
#define PD_ENDTERMEMPTY                -307782
#define PD_TERMLENEMPTY                -307784
#define PD_TERMLENSPEC                 -307786
#define PD_INSIDEXISTASLONG            -307788
#define PD_INSLONGEXISTASID            -307790
#define PD_TMREPONOTALLOWED            -307792
#define PD_SWBTYPEEMPTY                -307794
#define PD_FUTBOXTYPEEMPTY             -307796
#define PD_REFMUSTBETFORW              -307798
#define PD_CHFOUND                     -307800
#define PD_INVFULLDEPTH                -307802
#define PD_DESEXCEMPTY                 -307804
#define PD_PMMOBLTYPEINV               -307806
#define PD_SERIESSTATUSINV             -307808
#define PD_DEPOSTYPEINV                -307810
#define PD_OPERATIONINV                -307812
#define PD_INVIMPLDATE                 -307814
#define PD_WRONGDGRIMPLDATE            -307816
#define PD_INVHEDGEMEMBER              -307818
#define PD_WKPIDEMPTY                  -307820
#define PD_NOWKP                       -307822
#define PD_NOWKPACT                    -307824
#define PD_REFTOWKP                    -307826
#define PD_INVOBLEVEL                  -307828
#define PD_INVEXTFULLDEPTH             -307830
#define PD_INVINTFULLDEPTH             -307832
#define PD_INVDAYINWEEK                -307834
#define PD_INVWEEKINMONTH              -307836
#define PD_RATIOEXCEEDED               -307838
#define PD_NOMCSDATA                   -307840
#define PD_MCSCHKFAILED                -307842
#define PD_DIFFUNDERL                  -307844
#define PD_ILLRATIO                    -307846
#define PD_NOCBX                       -307848
#define PD_CBXIDEMPTY                  -307850
#define PD_BOXTYPEEMPTY                -307852
#define PD_REFTOCBX                    -307854
#define PD_DOUBLEOLEG                  -307856
#define PD_BOXALRSUSP                  -307858
#define PD_BOXALRRESUMED               -307860
#define PD_LEGMUSTBEOPSWPLEG           -307862
#define PD_NOCBS                       -307864
#define PD_NOCBSACT                    -307866
#define PD_SORTTYPEEMPTY               -307868
#define PD_WRONGPRFORMAT               -307870
#define PD_NEGVALNOTALLOWED            -307872
#define PD_NOCCR                       -307874
#define PD_NOCCRACT                    -307876
#define PD_CCRIDEMPTY                  -307878
#define PD_ACCRINTUDEMPTY              -307880
#define PD_CLEANPRUDEMPTY              -307882
#define PD_DAYCCONVEMPTY               -307884
#define PD_EOMCCONVEMPTY               -307886
#define PD_CALCCEMPTY                  -307888
#define PD_SNSFREETEXTEMPTY            -307890
#define PD_SNSNOOFSUBEMPTY             -307892
#define PD_SNSTERMPARAMEMPTY           -307894
#define PD_LONGSNSIDEMPTY              -307896
#define PD_TERMSNSIDEMPTY              -307898
#define PD_INCLOPTPREMEMPTY            -307900
#define PD_NOPRF                       -307902
#define PD_NOPRFACT                    -307904
#define PD_PRFIDEMPTY                  -307906
#define PD_OPTMIDPREMPTY               -307908
#define PD_GROSSORNETEMPTY             -307910
#define PD_DOUBLEPRF                   -307912
#define PD_TERMIDSPEC                  -307914
#define PD_NOIXV                       -307916
#define PD_NOIXVACT                    -307918
#define PD_IXVIDEMPTY                  -307920
#define PD_DOUBLEIXDATE                -307922
#define PD_NOCRO                       -307924
#define PD_NOCROACT                    -307926
#define PD_CROIDEMPTY                  -307928
#define PD_IXDATEEMPTY                 -307930
#define PD_IXVALEMPTY                  -307932
#define PD_IXVIDNOTEMPTY               -307934
#define PD_IXVALNOTEMPTY               -307936
#define PD_LAGISEMPTY                  -307938
#define PD_LAGISNOTEMPTY               -307940
#define PD_DECINDEXNOTEMPTY            -307942
#define PD_PROTCOUPNOTEMPTY            -307944
#define PD_PROTREDEMPTNOTEMPTY         -307946
#define PD_ILLSTARTHOUR                -307948
#define PD_ILLSTOPHOUR                 -307950
#define PD_ILLCASCHOUR                 -307952
#define PD_ILLSTARTMIN                 -307954
#define PD_ILLSTOPMIN                  -307956
#define PD_ILLCASCMIN                  -307958
#define PD_COUNTERPINFOEMPTY           -307960
#define PD_CURTYPEMPTY                 -307962
#define PD_CURTYPNOTEMPTY              -307964
#define PD_REFTOGCC                    -307966
#define PD_DELTAALLOCTIMESPEC          -307968
#define PD_TZISEMPTY                   -307970
#define PD_NOOFSERISZERO               -307972
#define PD_NOOFSEREXCEED               -307974
#define PD_NOOFUSRISZERO               -307976
#define PD_NOGWY                       -307978
#define PD_NOGWYACT                    -307980
#define PD_PQFOPEMPTY                  -307982
#define PD_SOPQFOPEMPTY                -307984
#define PD_CLASSLIMGTTOTAL             -307986
#define PD_WRONGCLASSQUERY             -307988
#define PD_WRONGCLASSTRANS             -307990
#define PD_LOWERLIMWRONG               -307992
#define PD_UPPERLIMWRONG               -307994
#define PD_STEPSIZEWRONG               -307996
#define PD_MTMPRICEWRONG               -307998
#define PD_NOCMI                       -308000
#define PD_NOCMIACT                    -308002
#define PD_CMIIDEMPTY                  -308004
#define PD_NOCSC                       -308006
#define PD_NOCSCACT                    -308008
#define PD_CSCIDEMPTY                  -308010
#define PD_CMIFORMATEMPTY              -308012
#define PD_LIFETYPEEMPTY               -308014
#define PD_AMOUNTEMPTY                 -308016
#define PD_PASSAGGREMPTY               -308018
#define PD_REFTOCSC                    -308020
#define PD_DOUBLECMI                   -308022
#define PD_LINKTYPEEMPTY               -308024
#define PD_DOUBLETZ                    -308026
#define PD_IMPLIMMNOTALLOWED           -308028
#define PD_LTDAFTERCLOSENOTALLOWED     -308030
#define PD_TOOMANYCBX                  -308032
#define PD_WRONGHOLDTIME               -308034
#define PD_MAXCOUPON                   -308036
#define PD_ONELINKAGE                  -308038
#define PD_NOSAR                       -308040
#define PD_NOSARACT                    -308042
#define PD_SARIDEMPTY                  -308044
#define PD_NODPR                       -308046
#define PD_NODPRACT                    -308048
#define PD_DPRIDEMPTY                  -308050
#define PD_NORIT                       -308052
#define PD_NORITACT                    -308054
#define PD_RITIDEMPTY                  -308056
#define PD_NORATEINS                   -308058
#define PD_NORATEINSACT                -308060
#define PD_RATEINSIDEMPTY              -308062
#define PD_REFTORIT                    -308064
#define PD_REFTOPOD                    -308066
#define PD_SECACCOUNTEMPTY             -308068
#define PD_CASHACCOUNTEMPTY            -308070
#define PD_DOUBLEACC                   -308072
#define PD_DOUBLERIT                   -308074
#define PD_REFTOCSA                    -308076
#define PD_REFTOSEC                    -308078
#define PD_FROMGEQTO                   -308080
#define PD_DOUBLEFROM                  -308082
#define PD_DOUBLETO                    -308084
#define PD_FROMOVRLAP                  -308086
#define PD_RITIDIDEMPTY                -308088
#define PD_RITIDNOTEMPTY               -308090
#define PD_TOOMANYACCOUNTS             -308092
#define PD_DOUBLEBIC                   -308094
#define PD_WRONGBIC                    -308096
#define PD_WRONGACC                    -308098
#define PD_BCDATEAFTCOUP               -308100
#define PD_BCDATEAFTMAT                -308102
#define PD_COUPBEFISS                  -308104
#define PD_BCDATEBEFISS                -308106
#define PD_COUPBEFDATED                -308108
#define PD_BCDATEBEFDATED              -308110
#define PD_INVMINIOBLEVEL              -308112
#define PD_GROUPTYPEEMPTY              -308114
#define PD_OPTTYPEEMPTY                -308116
#define PD_OPTSTYLEEMPTY               -308118
#define PD_REPOTYPEEMPTY               -308120
#define PD_SYNTHTYPEEMPTY              -308122
#define PD_MARTYPEEMPTY                -308124
#define PD_AVPERIODEMPTY               -308126
#define PD_SETTLCUREMPTY               -308128
#define PD_NOSETTLCUR                  -308130
#define PD_NOSETTLCURACT               -308132
#define PD_HOLIDAYADJEMPTY             -308134
#define PD_AGTIDEMPTY                  -308136
#define PD_NOAGT                       -308138
#define PD_NOAGTACT                    -308140
#define PD_EFTIDEMPTY                  -308142
#define PD_NOEFT                       -308144
#define PD_NOEFTACT                    -308146
#define PD_AGREEMENTEMPTY              -308148
#define PD_EFTSTIMULIEMPTY             -308150
#define PD_EXTFEETYPEEMPTY             -308152
#define PD_DOUBLEEXTFEE                -308154
#define PD_DOUBLEAGREEMENT             -308156
#define PD_CPNINTRSTISZERO             -308158
#define PD_CPNINTRSTNOTZERO            -308160
#define PD_COUPONSEXIST                -308162
#define PD_COUPONSNOTEXIST             -308164
#define PD_DAYCALCRULEWRONG            -308166
#define PD_COUPDATEWRONG               -308168
#define PD_BOOKSCLOSEDATEWRONG         -308170
#define PD_LOWERSTRIKEGEUPPER          -308172
#define PD_LOWEREXPGEUPPER             -308174
#define PD_DOUBLEUPPERSTRIKE           -308176
#define PD_DOUBLEUPPEREXP              -308178
#define PD_DOUBLELOWERSTRIKE           -308180
#define PD_DOUBLELOWEREXP              -308182
#define PD_LOWERSTRIKEOVRLAP           -308184
#define PD_LOWEREXPOVRLAP              -308186
#define PD_EXPLEZERO                   -308188
#define PD_LIMITNOTNEG                 -308190
#define PD_REFTOCIB                    -308192
#define PD_REFTOSID                    -308194
#define PD_REFTOPRL                    -308196
#define PD_NOSPL                       -308198
#define PD_NOSPLACT                    -308200
#define PD_NOEDL                       -308202
#define PD_NOEDLACT                    -308204
#define PD_SPLIDEMPTY                  -308206
#define PD_EDLIDEMPTY                  -308208
#define PD_PRICELIMITUNITEMPTY         -308210
#define PD_GWTIDEMPTY                  -308212
#define PD_LIMITTOSMALL                -308214
#define PD_NOGWT                       -308216
#define PD_NOGWTACT                    -308218
#define PD_UNLIMORLIMIT                -308220
#define PD_SETACTION                   -308222
#define PD_REFTOGWY                    -308224
#define PD_NOTLIMITTOHIGH              -308226
#define PD_ITMHIGHDITM                 -308228
#define PD_ATMHIGHOTM                  -308230
#define PD_STARTDATENOTEMPTY           -308232
#define PD_STOPDATENOTEMPTY            -308234
#define PD_OPTTYPENOTEMPTY             -308236
#define PD_OPTSTYLENOTEMPTY            -308238
#define PD_FUTSTYLEDSPEC               -308240
#define PD_WARRANTSPEC                 -308242
#define PD_REPOTYPENOTEMPTY            -308244
#define PD_BUYSELLBACKSPEC             -308246
#define PD_SYNTHTYPENOTEMPTY           -308248
#define PD_NONTRADREFSPEC              -308250
#define PD_CONTRSIZOPNOTEMPTY          -308252
#define PD_PQFOPNOTEMPTY               -308254
#define PD_BINDEALSNOTYES              -308256
#define PD_BILATCLNOTYES               -308258
#define PD_STARTTERMWRONG              -308260
#define PD_EXCCODEEXCEED               -308262
#define PD_MARCODEEXCEED               -308264
#define PD_INGCODEEXCEED               -308266
#define PD_CBGCODEEXCEED               -308268
#define PD_COMCODEEXCEED               -308270
#define PD_DOUBLEMARORDACT             -308272
#define PD_DIFFLTTPARAM                -308274
#define PD_DIFFIMSCHARGE               -308276
#define PD_DIFFICSCREDITRATE           -308278
#define PD_MAXLEGEXCEED                -308280
#define PD_DOUBLEDEFINED               -308282
#define PD_REFTOSSS                    -308284
#define PD_ECBIDEMPTY                  -308286
#define PD_NOECB                       -308288
#define PD_NOECBACT                    -308290
#define PD_SSSIDEMPTY                  -308292
#define PD_NOSSS                       -308294
#define PD_NOSSSACT                    -308296
#define PD_REFTOECB                    -308298
#define PD_STATEREFORLAST              -308300
#define PD_NORRD                       -308302
#define PD_NORRDACT                    -308304
#define PD_RRDIDEMPTY                  -308306
#define PD_NORSP                       -308308
#define PD_NORSPACT                    -308310
#define PD_RSPIDEMPTY                  -308312
#define PD_DOUBLERRD                   -308314
#define PD_REFTORRD                    -308316
#define PD_REFTORUP                    -308318
#define PD_RUPIDEMPTY                  -308320
#define PD_RUNNUMBEREMPTY              -308322
#define PD_NORUP                       -308324
#define PD_NORUPACT                    -308326
#define PD_CLOSEONLYNOTALLWD           -308328
#define PD_DOUBLESTRESSMAR             -308330
#define PD_NOTINDATAGEN                -308332
#define PD_DOUBLEBASICSCEN             -308334
#define PD_PQRPUBIDEMPTY               -308336
#define PD_EFTALLEMPTY                 -308338
#define PD_NODSC                       -308340
#define PD_NODSCACT                    -308342
#define PD_REFTOEFT                    -308344
#define PD_PERNOLIM                    -308346
#define PD_WRONGREFPRICEFORMAT         -308348
#define PD_ENQREQEMPTY                 -308350
#define PD_COMPREQEMPTY                -308352
#define PD_GWYILLCHAR                  -308354
#define PD_GWYGENERICEXIST             -308356
#define PD_TMNOTALLWDFROMPD            -308358
#define PD_REFTOAUR                    -308360
#define PD_AURIDEMPTY                  -308362
#define PD_NOAUR                       -308364
#define PD_NOAURACT                    -308366
#define PD_TRTNOTAUTH                  -308368
#define PD_DOUBLEAUR                   -308370
#define PD_HCTIDEMPTY                  -308372
#define PD_NOHCT                       -308374
#define PD_NOHCTACT                    -308376
#define PD_HAIRCREMPTY                 -308378
#define PD_NOCVR                       -308380
#define PD_NOCVRACT                    -308382
#define PD_NOCOR                       -308384
#define PD_NOCORACT                    -308386
#define PD_ACCEPTCOLLWRONG             -308388
#define PD_CVRIDEMPTY                  -308390
#define PD_CORIDEMPTY                  -308392
#define PD_COLLTYPEEMPTY               -308394
#define PD_NOATY                       -308396
#define PD_FRBIDEMPTY                  -308398
#define PD_NOFRB                       -308400
#define PD_NOFRBACT                    -308402
#define PD_NOCONSBNK                   -308404
#define PD_NOCONSBNKACT                -308406
#define PD_CONSBNKIDEMPTY              -308408
#define PD_PVMIDEMPTY                  -308410
#define PD_NOPVM                       -308412
#define PD_NOPVMACT                    -308414
#define PD_VMAIDEMPTY                  -308416
#define PD_NOVMA                       -308418
#define PD_NOVMAACT                    -308420
#define PD_CRMIDEMPTY                  -308422
#define PD_NOCRM                       -308424
#define PD_NOCRMACT                    -308426
#define PD_COLLACCEMPTY                -308428
#define PD_INTERACCEMPTY               -308430
#define PD_VOLADAYSEMPTY               -308432
#define PD_PVMMANYROWS                 -308434
#define PD_DOUBLEPVM                   -308436
#define PD_VOLCORRMISS                 -308438
#define PD_DOUBLEVMA                   -308440
#define PD_DOUBLECRM                   -308442
#define PD_XYMISSMATCH                 -308444
#define PD_VALNOTONE                   -308446
#define PD_REFTOPSR                    -308448
#define PD_XYTOOSMALL                  -308450
#define PD_INVTZTRANSITION             -308452
#define PD_NOOAT                       -308454
#define PD_NOOATACT                    -308456
#define PD_NOPQC                       -308458
#define PD_NOPQCACT                    -308460
#define PD_OATIDEMPTY                  -308462
#define PD_DOUBLEPQC                   -308464
#define PD_PQCIDEMPTY                  -308466
#define PD_EXTLARGERINT                -308468
#define PD_REFTOWIG                    -308470
#define PD_WIGIDEMPTY                  -308472
#define PD_NOWIG                       -308474
#define PD_NOWIGACT                    -308476
#define PD_DOUBLEWIG                   -308478
#define PD_REFTOTDG                    -308480
#define PD_TDGIDEMPTY                  -308482
#define PD_NOTDG                       -308484
#define PD_NOTDGACT                    -308486
#define PD_DOUBLETDG                   -308488
#define PD_RECTPOS                     -308490
#define PD_KEEPOSCHANGED               -308492
#define PD_GIVERECTEMPTY               -308494
#define PD_DOUBLEDRE                   -308496
#define PD_REFTODRE                    -308498
#define PD_HCTOUTRANGE                 -308500
#define PD_REFTOFRB                    -308502
#define PD_NEWCSTIDEMPTY               -308504
#define PD_INVSWIFTMEM                 -308506
#define PD_NOTMPLCST                   -308508
#define PD_DERIVLEVWRONG               -308510
#define PD_INSILLSUSPEND               -308512
#define PD_INVALIDTIME                 -308514
#define PD_SSTNOTEMPTY                 -308516
#define PD_ACTOLOTEMPTY                -308518
#define PD_LOTTYPEEMPTY                -308520
#define PD_LONORDACTEMPTY              -308522
#define PD_DOUBLELOTTYPE               -308524
#define PD_MAXLOTEXCEED                -308526
#define PD_ODDLOTNOTONE                -308528
#define PD_ROUNDNOTFOUND               -308530
#define PD_ROUNDLTODD                  -308532
#define PD_ROUNDMISSING                -308534
#define PD_BLOCKNOTMULT                -308536
#define PD_DATEFEMPTY                  -308538
#define PD_DATEFNOTEMPTY               -308540
#define PD_TRADINGCEXIST               -308542
#define PD_GROUPEXISTASCOMBO           -308544
#define PD_COMBOEXISTASGROUP           -308546
#define PD_NORMALNOTMULT               -308548
#define PD_DELTAVALUEEMPTY             -308550
#define PD_HALFSTEPSEMPTY              -308552
#define PD_ENABLEDELTAWRONG            -308554
#define PD_ENABLEHALFWRONG             -308556
#define PD_HALFABOVEEXCABOVE           -308558
#define PD_HALFBELOWEXCBELOW           -308560
#define PD_FTTIMENOTEMPTY              -308562
#define PD_FTTIMEEMPTY                 -308564
#define PD_LTTIMENOTEMPTY              -308566
#define PD_LTTIMEEMPTY                 -308568
#define PD_FTDATEBEFORECRE             -308570
#define PD_FTDMOVBACK                  -308572
#define PD_FTDMOVFORW                  -308574
#define PD_TRADEDINCLICKWRONG          -308576
#define PD_CLASSISTRADEDCLK            -308578
#define PD_INTNOTTRADEDCLK             -308580
#define PD_SERISTRADEDCLK              -308582
#define PD_INCNOTTRADEDCLK             -308584
#define PD_INSNOTYETTRADED             -308586
#define PD_FIRSTDATEAFTER              -308588
#define PD_FIRSTTIMEAFTER              -308590
#define PD_MAXDIFFLASTEXCEED           -308592
#define PD_MAXDIFFFIRSTEXCEED          -308594
#define PD_PRICEISMISSING              -308596
#define PD_MORETHANONELEVELSPEC        -308598
#define PD_SIGNALPARTLY                -308600
#define PD_SPECIFYONELEVEL             -308602
#define PD_RCLASSEMPTY                 -308604
#define PD_RCADJEMPTY                  -308606
#define PD_REFTORSP                    -308608
#define PD_DOUBLERRC                   -308610
#define PD_NOVALIDRNKCLASS             -308612
#define PD_LTMIDEMPTY                  -308614
#define PD_NOLTM                       -308616
#define PD_NOLTMACT                    -308618
#define PD_NOLTMFOUND                  -308620
#define PD_INVALIDRRC                  -308622
#define PD_DOUBLERUP                   -308624
#define PD_OPTVAREMPTY                 -308626
#define PD_KNOCKVAREMPTY               -308628
#define PD_BINARYVAREMPTY              -308630
#define PD_SWAPSTYLEEMPTY              -308632
#define PD_FORWSTYLEEMPTY              -308634
#define PD_FORWSTYLEWRONG              -308636
#define PD_SWAPSTYLEWRONG              -308638
#define PD_KNOCKVARWRONG               -308640
#define PD_BINARYVARWRONG              -308642
#define PD_TRROVERMAX                  -308644
#define PD_REFTOLTM                    -308646
#define PD_MARIDXDIFF                  -308648
#define PD_LTMIDXDIFF                  -308650
#define PD_NOVIRTCOM                   -308652
#define PD_NOVIRTCOMACT                -308654
#define PD_NOLINKCOM                   -308656
#define PD_NOLINKCOMACT                -308658
#define PD_NOVSC                       -308660
#define PD_NOVSCACT                    -308662
#define PD_NOPID                       -308664
#define PD_NOPIDACT                    -308666
#define PD_DOUBLECBC                   -308668
#define PD_BOTHINGCBG                  -308670
#define PD_REFTOSTS                    -308672
#define PD_SECCODEEMPTY                -308674
#define PD_CRPCODEEMPTY                -308676
#define PD_PIDIDEMPTY                  -308678
#define PD_PARTALREXISTS               -308680
#define PD_REFTOCPA                    -308682
#define PD_COMINCINSEMPTY              -308684
#define PD_COMINCINSNOTEMPTY           -308686
#define PD_STARTNOTVALID               -308688
#define PD_ENDBEFORESTART              -308690
#define PD_RECORDBEFORESTART           -308692
#define PD_AFFECTLINKWRONG             -308694
#define PD_NOCAC                       -308696
#define PD_NOCACACT                    -308698
#define PD_MINSIZEWRONG                -308700
#define PD_MAXSIZEWRONG                -308702
#define PD_INVOBLEVELBIG               -308704
#define PD_INVMINIOBLEVELBIG           -308706
#define PD_SESSNOEMPTY                 -308708
#define PD_DOUBLESESSNO                -308710
#define PD_WRONGVIRTUAL                -308712
#define PD_LINKISSAME                  -308714
#define PD_LINKISLINKED                -308716
#define PD_COMISLINKED                 -308718
#define PD_DOUBLECRP                   -308720
#define PD_VIRTINCNOTALLWD             -308722
#define PD_VIRTCBCNOTALLWD             -308724
#define PD_VIRTININC                   -308726
#define PD_VIRTINCBC                   -308728
#define PD_EXRALREXIST                 -308730
#define PD_EXRCURTYPE                  -308732
#define PD_INDEXCOMEMPTY               -308734
#define PD_WRONGMARATTR                -308736
#define PD_WRONGINGATTR                -308738
#define PD_WRONGCBGATTR                -308740
#define PD_ABBRNOTUNIQUE               -308742
#define PD_STOCKCODENOTUNIQUE          -308744
#define PD_SEQNOTUNIQUE                -308746
#define PD_NOCOMCODELEFT               -308748
#define PD_STKHPNAMEEMPTY              -308750
#define PD_STKSHNAMEEMPTY              -308752
#define PD_STKWHNISSDTEEMPTY           -308754
#define PD_STKSECTYPEEMPTY             -308756
#define PD_STKEXPDATEEMPTY             -308758
#define PD_STKPAREMPTY                 -308760
#define PD_STKPARCUREMPTY              -308762
#define PD_STKLOTEMPTY                 -308764
#define PD_STKCOUEMPTY                 -308766
#define PD_STKTRDCUREMPTY              -308768
#define PD_STKMKTWRONG                 -308770
#define PD_STKISINEMPTY                -308772
#define PD_STKPARCDEEMPTY              -308774
#define PD_STKWIWRONG                  -308776
#define PD_STKSECTCEMPTY               -308778
#define PD_STKTRADEDWRONG              -308780
#define PD_STKCODEEMPTY                -308782
#define PD_STKIBMCDEEMPTY              -308784
#define PD_STKRMASTEREMPTY             -308786
#define PD_STKCMASTEREMPTY             -308788
#define PD_STKIMASTEREMPTY             -308790
#define PD_STKDMASTEREMPTY             -308792
#define PD_STKCMASTERWRONG             -308794
#define PD_STKIMASTERWRONG             -308796
#define PD_STKDMASTERWRONG             -308798
#define PD_STKINVSCHWRONG              -308800
#define PD_STKSECUATTRWRONG            -308802
#define PD_STKCHGIDENTEMPTY            -308804
#define PD_HP_NOACTION                  308805
#define PD_STKDELIDENTEMPTY            -308806
#define PD_STKAMENDCDEWRONG            -308808
#define PD_NOPLSTATE                   -308810
#define PD_WHNISSDTEWRONG              -308812
#define PD_NOWICODE                    -308814
#define PD_LINKNOTALLWD                -308816
#define PD_LINKISVIRTUAL               -308818
#define PD_IMMISSINSWRONG              -308820
#define PD_IMMISSCOMWRONG              -308822
#define PD_ISSENDDATEWRONG             -308824
#define PD_WARNINGINTWRONG             -308826
#define PD_ORDACTEMPTY                 -308828
#define PD_NOCORPLEV                   -308830
#define PD_IMMISSWRONG                 -308832
#define PD_CRPWRONG                    -308834
#define PD_CRPTYPEEMPTY                -308836
#define PD_MINGTMAX                    -308838
#define PD_REFTOSST                    -308840
#define PD_HIDDOATNOTALLWD             -308842
#define PD_HIDDCBTNOTALLWD             -308844
#define PD_MINVALGTMAX                 -308846
#define PD_MINVOLGTMAX                 -308848
#define PD_SETTLMACTEMPTY              -308850
#define PD_CRPCODEWRONG                -308852
#define PD_NOEXD                       -308854
#define PD_NOEXDACT                    -308856
#define PD_EXDIDEMPTY                  -308858
#define PD_REFTOEXD                    -308860
#define PD_DOUBLEEXCEPTDATE            -308862
#define PD_CHGATTREMPTY                -308864
#define PD_ACPNAMEEMPTY                -308866
#define PD_ACPIDEMPTY                  -308868
#define PD_DOUBLECLP                   -308870
#define PD_ONEDEFAULT                  -308872
#define PD_NODEFAULT                   -308874
#define PD_ALLCHARSET                  -308876
#define PD_REPCHAR                     -308878
#define PD_REQALPHA                    -308880
#define PD_REQDIGIT                    -308882
#define PD_REQEXT                      -308884
#define PD_REQDIC                      -308886
#define PD_STARTBEFIMPL                -308888
#define PD_ISSENDPASSED                -308890
#define PD_ILLEGTIME                   -308892
#define PD_NOASC                       -308894
#define PD_NOASCACT                    -308896
#define PD_ASCIDEMPTY                  -308898
#define PD_NODSTSST                    -308900
#define PD_NODSTSSTACT                 -308902
#define PD_DSTSSTIDEMPTY               -308904
#define PD_NOTRISST                    -308906
#define PD_NOTRISSTACT                 -308908
#define PD_TRISSTIDEMPTY               -308910
#define PD_DOUBLEDSTSST                -308912
#define PD_REFTOASC                    -308914
#define PD_NOMOVINS                    -308916
#define PD_NOMOVINSACT                 -308918
#define PD_ASCTIMEOUTEMPTY             -308920
#define PD_PRACTSECNOTALLWD            -308922
#define PD_TRDCURUNITEMPTY             -308924
#define PD_CURUNITEMPTY                -308926
#define PD_NOSLI                       -308928
#define PD_NOSLIACT                    -308930
#define PD_SLIIDEMPTY                  -308932
#define PD_REFTOSLI                    -308934
#define PD_DOUBLEMAR                   -308936
#define PD_REFTOUST                    -308938
#define PD_DOUBLEENDSTATE              -308940
#define PD_NOENDSTATE                  -308942
#define PD_WRONGCSTATTR                -308944
#define PD_WRONGOLDPASSW               -308946
#define PD_ILLOLDPASSW                 -308948
#define PD_ILLCROSSMARKET              -308950
#define PD_STKLOTEXCEEDED              -308952
#define PD_STKLOTNOTNUM                -308954
#define PD_STKPARNOTNUM                -308956
#define PD_STKRMASTERNOTNUM            -308958
#define PD_STKCMASTERNOTNUM            -308960
#define PD_STKIMASTERNOTNUM            -308962
#define PD_STKDMASTERNOTNUM            -308964
#define PD_REFNUMBZERO                 -308966
#define PD_REMOVEINTRNOTALLWD          -308968
#define PD_WRONGOWNMEM                 -308970
#define PD_COLDRESTEMPTY               -308972
#define PD_NOAGR                       -308974
#define PD_NOAGRACT                    -308976
#define PD_AGRIDEMPTY                  -308978
#define PD_REFTOAGR                    -308980
#define PD_DOUBLEAGR                   -308982
#define PD_BOTHAGRCLASS                -308984
#define PD_NONPRACTSECNOTALLWD         -308986
#define PD_PRACTSECMIXNOTALLWD         -308988
#define PD_PASSWCHSETEMPTY             -308990
#define PD_ILLSSSSTART                 -308992
#define PD_ILLSSSTIMESEQ               -308994
#define PD_COMLINKILLSTATUS            -308996
#define PD_LINKEDDELISTED              -308998
#define PD_TRDDISSEMPTY                -309000
#define PD_MAXEXTCOUPON                -309002
#define PD_OPIFSELLWRONG               -309004
#define PD_OPPIDEMPTY                  -309006
#define PD_NOOPP                       -309008
#define PD_NOOPPACT                    -309010
#define PD_DIOIDEMPTY                  -309012
#define PD_NODIO                       -309014
#define PD_NODIOACT                    -309016
#define PD_BLKCROIDEMPTY               -309018
#define PD_DOUBLEPOD                   -309020
#define PD_ORIGINNOTSPEC               -309022
#define PD_NOLSS                       -309024
#define PD_NOLSSACT                    -309026
#define PD_NOSLP                       -309028
#define PD_NOSLPACT                    -309030
#define PD_LSSNOTEMPTY                 -309032
#define PD_LSSIDEMPTY                  -309034
#define PD_DOUBLESST                   -309036
#define PD_SLPIDEMPTY                  -309038
#define PD_REFTOLSS                    -309040
#define PD_REFTOICS                    -309042
#define PD_DOUBLEREX                   -309044
#define PD_ACCTIDEMPTY                 -309046
#define PD_ACCTIDNOTEMPTY              -309048
#define PD_OBJIDEMPTY                  -309050
#define PD_OBJTYPEWRONG                -309052
#define PD_SHRTSPSIDEMPTY              -309054
#define PD_SHRTSRUIDEMPTY              -309056
#define PD_NOSHRTSPS                   -309058
#define PD_NOSHRTSPSACT                -309060
#define PD_NOSHRTSRU                   -309062
#define PD_NOSHRTSRUACT                -309064
#define PD_NOAQR                       -309066
#define PD_NOAQRACT                    -309068
#define PD_AQRIDEMPTY                  -309070
#define PD_AQRFREQWRONG                -309072
#define PD_NOOFEXPWRONG                -309074
#define PD_NOOFOTMWRONG                -309076
#define PD_NOOFITMWRONG                -309078
#define PD_MDCINTERVWRONG              -309080
#define PD_AQRSTARTWRONG               -309082
#define PD_AQRSTARTEXCEEDED            -309084
#define PD_AQRINTERVWRONG              -309086
#define PD_AQRINTERVEXCEEDED           -309088
#define PD_NOOFCYCLEWRONG              -309090
#define PD_AQRCYCLEWAITWRONG           -309092
#define PD_AQRCYCLEWAITEXCEEDED        -309094
#define PD_EXQRTIMEWRONG               -309096
#define PD_AQRCHECKWRONG               -309098
#define PD_REFTOCEG                    -309100
#define PD_SECLENDTYPEEMPTY            -309102
#define PD_NORPG                       -309104
#define PD_NORPGACT                    -309106
#define PD_REFTOBNK                    -309108
#define PD_RPTVISIBEMPTY               -309110
#define PD_RPTFILEPREFEMPTY            -309112
#define PD_RPTFILEEXTEMPTY             -309114
#define PD_RPTSCHEDEMPTY               -309116
#define PD_RPTTYPEEMPTY                -309118
#define PD_RTMIDEMPTY                  -309120
#define PD_PARAMNOEMPTY                -309122
#define PD_PARAMNAMEEMPTY              -309124
#define PD_PARAMTYPEEMPTY              -309126
#define PD_REFTORTM                    -309128
#define PD_PARAMINPVEMPTY              -309130
#define PD_DOUBLEPARAM                 -309132
#define PD_WRONGPARAM                  -309134
#define PD_EXCPARAMMISSING             -309136
#define PD_RPTIDEMPTY                  -309138
#define PD_RPTEVENTEMPTY               -309140
#define PD_NORTM                       -309142
#define PD_NORTMACT                    -309144
#define PD_NORPT                       -309146
#define PD_NORPTACT                    -309148
#define PD_RPTWHENEMPTY                -309150
#define PD_REFTORPT                    -309152
#define PD_RPTSPECNOTUNIQUE            -309154
#define PD_RPTSPECDESCEMPTY            -309156
#define PD_RPTSUBSYSEMPTY              -309158
#define PD_RPTSUBSYSNOTEMPTY           -309160
#define PD_RDTIDEMPTY                  -309162
#define PD_RDTIDNOTEMPTY               -309164
#define PD_PRDIDNOTEMPTY               -309166
#define PD_DOUBLERPI                   -309168
#define PD_RPTPRODWRONG                -309170
#define PD_RPGIDEMPTY                  -309172
#define PD_REFTORPG                    -309174
#define PD_BOTHRPGREPSPEC              -309176
#define PD_RPGINRPG                    -309178
#define PD_DOUBLERPG                   -309180
#define PD_RDTTIMEEMPTY                -309182
#define PD_RDTDAYNOEMPTY               -309184
#define PD_RDTBOTHTIMEDEF              -309186
#define PD_DOUBLERDT                   -309188
#define PD_REFTORDT                    -309190
#define PD_NORDT                       -309192
#define PD_NORDTACT                    -309194
#define PD_NOTAUTHORIZEDCLH            -309196
#define PD_REFTOCSB                    -309198
#define PD_CLHISCHANGED                -309200
#define PD_NAMEDWRONG                  -309202
#define PD_WRONGPARAM2                 -309204
#define PD_OTTIMEEMPTY                 -309206
#define PD_RDTISEMPTY                  -309208
#define PD_ACTONEMPTY                  -309210
#define PD_ACTONWRONG                  -309212
#define PD_WRONGVALIDUNTIL             -309214
#define PD_DOUBLELTT                   -309216
#define PD_LTTUNLIMNOTALLWD            -309218
#define PD_LTTOVERLAPPING              -309220
#define PD_WRLTTTIMENONE               -309222
#define PD_SHRTTERMUNITEMPTY           -309224
#define PD_RTMFILENOTUNIQUE            -309226
#define PD_REFTOCBA                    -309228
#define PD_NOREFPRICE                  -309230
#define PD_ERROPENFILE                 -309232
#define PD_NOOFINSWRONG                -309234
#define PD_WRONGCLASSTXQ               -309236
#define PD_WRONGCLASSTXR               -309238
#define PD_EXCIDNOTREQ                 -309240
#define PD_EXCIDREQFORTDG              -309242
#define PD_TDPTDGEMPTY                 -309244
#define PD_CONVSERIESEXIST             -309246
#define PD_BOTHINTABT                  -309248
#define PD_REFTOABT                    -309250
#define PD_NOABT                       -309252
#define PD_NOABTACT                    -309254
#define PD_ABTIDEMPTY                  -309256
#define PD_INVMDSTARTEND               -309258
#define PD_CLEARDAYSEMPTY              -309260
#define PD_ERRCLOSECLEARING            -309262
#define PD_ERROPENTRADING              -309264
#define PD_REFTOMPR                    -309266
#define PD_MPRIDEMPTY                  -309268
#define PD_NOMPR                       -309270
#define PD_NOMPRACT                    -309272
#define PD_DOUBLECST                   -309274
#define PD_PPPERCEMPTY                 -309276
#define PD_PPPERCEXCEEDED              -309278
#define PD_MM1PERCEMPTY                -309280
#define PD_MM2PERCEMPTY                -309282
#define PD_MM3PERCEMPTY                -309284
#define PD_MM4PERCEMPTY                -309286
#define PD_MM5PERCEMPTY                -309288
#define PD_MM1PERCEXCEEDED             -309290
#define PD_MMALLWARNEMPTY              -309292
#define PD_MM2PERCEXCEEDED             -309294
#define PD_MM3PERCEXCEEDED             -309296
#define PD_MM4PERCEXCEEDED             -309298
#define PD_MM5PERCEXCEEDED             -309300
#define PD_MMALLWARNEXCEEDED           -309302
#define PD_RANKEXCEEDED                -309304
#define PD_RANKEMPTY                   -309306
#define PD_MATCHPRIONOTALLWD           -309308
#define PD_INVALIDVERSION              -309310
#define PD_WCCALRCHILD                 -309312
#define PD_HOLDINGNOTALLWD             -309314
#define PD_NOWRACCESS                  -309316
#define PD_COUNTERSNOTALLWD            -309318
#define PD_ALRCOUNTERSIGNED            -309320
#define PD_NOCEG                       -309322
#define PD_NOCPA                       -309324
#define PD_NOCSA                       -309326
#define PD_NOSEC                       -309328
#define PD_NODLV                       -309330
#define PD_NODRE                       -309332
#define PD_NOICO                       -309334
#define PD_NOISN                       -309336
#define PD_NOISS                       -309338
#define PD_NOITU                       -309340
#define PD_NOMNA                       -309342
#define PD_NOPQR                       -309344
#define PD_COUNTERSIMMNOTALLWD         -309346
#define PD_DELHOLDINGNOTALLWD          -309348
#define PD_COUNTERSINSNOTALLWD         -309350
#define PD_NOCDC                       -309352
#define PD_NOGCG                       -309354
#define PD_UPDHOLDINGDELNOTALLWD       -309356
#define PD_NEWINSISWRONG               -309358
#define PD_SOINSISWRONG                -309360
#define PD_REFTOCBG                    -309362
#define PD_ACCCOMBOFIRST               -309364
#define PD_NOSTY                       -309366
#define PD_NOSTYACT                    -309368
#define PD_STYIDEMPTY                  -309370
#define PD_NOPTM                       -309372
#define PD_NOPTMACT                    -309374
#define PD_PTMIDEMPTY                  -309376
#define PD_FROMEXPEMPTY                -309378
#define PD_STPMULTEMPTY                -309380
#define PD_DOUBLEFROMEXP               -309382
#define PD_MULTIPLEWRONG               -309384
#define PD_FROMEXP1MISSING             -309386
#define PD_WRONGCUSTATTRRULE           -309388
#define PD_WRONGACCATTRRULE            -309390
#define PD_WRONGREADATTRRULE           -309392
#define PD_WRONGDIARYATTRRULE          -309394
#define PD_WRONGATYATTRRULE            -309396
#define PD_WRONGAFTATTRRULE            -309398
#define PD_WRONGCSBATTRRULE            -309400
#define PD_WRONGCCCSTATTRRULE          -309402
#define PD_WRONGANETATTRRULE           -309404
#define PD_WRONGCURATTRRULE            -309406
#define PD_WRONGCURCONVATTRRULE        -309408
#define PD_WRONGRMNATTRRULE            -309410
#define PD_WRONGINVTATTRRULE           -309412
#define PD_WRONGNATIONATTRRULE         -309414
#define PD_WRONGACCTEXTATTRRULE        -309416
#define PD_WRONGEXTACCATTRRULE         -309418
#define PD_WRONGFORHOLDATTRRULE        -309420
#define PD_BOTHINTMAR                  -309422
#define PD_BOTHINTMAREMPTY             -309424
#define PD_NODREACT                    -309426
#define PD_DREIDEMPTY                  -309428
#define PD_NORST                       -309430
#define PD_NORSTACT                    -309432
#define PD_RSTIDEMPTY                  -309434
#define PD_DOUBLERST                   -309436
#define PD_LTDAFTEREXP                 -309438
#define PD_LTDAFTEREFFEXP              -309440
#define PD_PREMUNITNOTEQ               -309442
#define PD_CURRUNITNOTEQ               -309444
#define PD_REFTOSTY                    -309446
#define PD_ZEROFIXEMPTY                -309448
#define PD_NOSCR                       -309450
#define PD_NOSCRACT                    -309452
#define PD_NOMCO                       -309454
#define PD_NOMCOACT                    -309456
#define PD_DOUBLEATY                   -309458
#define PD_REFTOMCO                    -309460
#define PD_WRONGNDSCRPARAM             -309462
#define PD_WRONGLTDSCRPARAM            -309464
#define PD_WRONGMCOACCOUNT             -309466
#define PD_MCOIDEMPTY                  -309468
#define PD_SCRONLYFOROPT               -309470
#define PD_NOMBS                       -309472
#define PD_NOMBSACT                    -309474
#define PD_MBSIDEMPTY                  -309476
#define PD_REFTOMBS                    -309478
#define PD_STKMBSEMPTY                 -309480
#define PD_ULRIDEMPTY                  -309482
#define PD_LOWCOMEMPTY                 -309484
#define PD_UPPCOMEMPTY                 -309486
#define PD_STOCKFROMEMPTY              -309488
#define PD_STOCKTOEMPTY                -309490
#define PD_LOWERCOMGEUPPER             -309492
#define PD_DOUBLESEQNO                 -309494
#define PD_FROMNOTALNUM                -309496
#define PD_TONOTALNUM                  -309498
#define PD_NOALNUMINSTOCK              -309500
#define PD_ULRNOTFOUND                 -309502
#define PD_REFTOULR                    -309504
#define PD_SEQNOEMPTY                  -309506
#define PD_NOULR                       -309508
#define PD_NOVOM                       -309510
#define PD_NOVOMACT                    -309512
#define PD_VOMIDEMPTY                  -309514
#define PD_OLDINSISCHANGED             -309516
#define PD_NEWINSISCHANGED             -309518
#define PD_SOINSISCHANGED              -309520
#define PD_MINIINCIDEMPTY              -309522
#define PD_NETRATIOEMPTY               -309524
#define PD_NETTINGINCALREADYEXIST      -309526
#define PD_INCALREADYEXIST             -309528
#define PD_NOCPNCST                    -309530
#define PD_NOCPNCSTACT                 -309532
#define PD_CPNCSTIDEMPTY               -309534
#define PD_CPNEXCIDEMPTY               -309536
#define PD_INCNETTINGSAME              -309538
#define PD_REFTOCPN                    -309540
#define PD_ACTIVEINSEXIST              -309542
#define PD_NOITEMFOUND                 -309544
#define PD_COMIDWRONG                  -309546
#define PD_NEWCOMIDEMPTY               -309548
#define PD_INCIDWRONG                  -309550
#define PD_TDPIDWRONG                  -309552
#define PD_PURIDWRONG                  -309554
#define PD_PURNOTEQ                    -309556
#define PD_POSIDEMPTY                  -309558
#define PD_NOCPN                       -309560
#define PD_KEEPOSHANDLCHANGED          -309562
#define PD_CSTINTSUSP                  -309564
#define PD_INVONOFFSUSP                -309566
#define PD_SKEWUPISWRONG               -309568
#define PD_SKEWDOWNISWRONG             -309570
#define PD_INVPRIORITY                 -309572
#define PD_SPREADUNITEMPTY             -309574
#define PD_ILLSESSALLOWED              -309576
#define PD_ACCMANUSER                  -309578
#define PD_USTALREADYRESUMED           -309580
#define PD_USTALREADYSUSP              -309582
#define PD_INVSUSPENDRESUME            -309584
#define PD_VAGIDEMPTY                  -309586
#define PD_NOVAG                       -309588
#define PD_NOVAGACT                    -309590
#define PD_USGIDEMPTY                  -309592
#define PD_NOUSG                       -309594
#define PD_NOUSGACT                    -309596
#define PD_INVADDUSG                   -309598
#define PD_INVDELUSG                   -309600
#define PD_MANTRDUSG                   -309602
#define PD_SLCIDEMPTY                  -309604
#define PD_NOSLC                       -309606
#define PD_NOSLCACT                    -309608
#define PD_WRONGOWNUSG                 -309610
#define PD_INVDAYCOUNTCONV             -309612
#define PD_INVBUSINESSDAYCONV          -309614
#define PD_INVRESETDAYTYPE             -309616
#define PD_INVPAYMENTSET               -309618
#define PD_ROLLOVERDATECALCFAILED      -309620
#define PD_INVFIXETFLOAYVALUE          -309622
#define PD_INVNBROFSWAPLEGS            -309624
#define PD_INVNBROFFRALEGS             -309626
#define PD_INVROLLOVERPERIOD           -309628
#define PD_INVSETTLEMENTDAYS           -309630
#define PD_PAYINADVANCENOTIRS          -309632
#define PD_INVSETTLEMENTDAYSADVANCE    -309634
#define PD_INVTRONOTRADED              -309636
#define PD_INVTCXTNOTRADED             -309638
#define PD_INVTRONOTRADEDCXT           -309640
#define PD_MANRESETINS                 -309642
#define PD_MANRESETHOLIDAY             -309644
#define PD_INVRESETDAYS                -309646
#define PD_NOTEMPTYRESETINS            -309648
#define PD_NOTEMPTYRESETHOLIDAY        -309650
#define PD_NOTZERORESETDAYS            -309652
#define PD_NOTEMPTYRESETTYPE           -309654
#define PD_INVLEGNO                    -309656
#define PD_INVSLCITEMS                 -309658
#define PD_SETTLHOLEMPTY               -309660
#define PD_NEGSETTLEMENTDAYS           -309662
#define PD_INVSLCGROUP                 -309664
#define PD_RESETHOLIDAYNOTFOUND        -309666
#define PD_SETTLEHOLIDAYNOTFOUND       -309668
#define PD_INVLEGNBRSWAP               -309670
#define PD_INVSWPSTYLCR                -309672
#define PD_INVLEGNBRFRA                -309674
#define PD_INVLEGTYPEFRA               -309676
#define PD_AIHIDEMPTY                  -309678
#define PD_REFTOAIH                    -309680
#define PD_NOAIH                       -309682
#define PD_NOAIHACT                    -309684
#define PD_REFTOVAG                    -309686
#define PD_CVREMPTY                    -309688
#define PD_NORFR                       -309690
#define PD_NORFRACT                    -309692
#define PD_RFRIDEMPTY                  -309694
#define PD_DETERMDATEEMPTY             -309696
#define PD_FROMDATEEMPTY               -309698
#define PD_RATEEMPTY                   -309700
#define PD_REFTORFR                    -309702
#define PD_DOUBLERFR                   -309704
#define PD_NOLOT                       -309706
#define PD_NOLOTACT                    -309708
#define PD_LOTIDEMPTY                  -309710
#define PD_LOTTERYDATEEMPTY            -309712
#define PD_PAYOUTDATEEMPTY             -309714
#define PD_REFTOLOT                    -309716
#define PD_DOUBLELOT                   -309718
#define PD_STFIDEMPTY                  -309720
#define PD_NOSTF                       -309722
#define PD_NOSTFACT                    -309724
#define PD_SFIIDEMPTY                  -309726
#define PD_NOSFI                       -309728
#define PD_NOSFIACT                    -309730
#define PD_CONVFROMEMPTY               -309732
#define PD_CONVTHROUGHEMPTY            -309734
#define PD_DOUBLECON                   -309736
#define PD_NOLEADCST                   -309738
#define PD_NOLEADCSTACT                -309740
#define PD_NOARRCST                    -309742
#define PD_NOARRCSTACT                 -309744
#define PD_NOCORRVPT                   -309746
#define PD_NOCORRVPTACT                -309748
#define PD_SSSTYPEEMPTY                -309750
#define PD_REFTOCIS                    -309752
#define PD_BOTHPRIONOTALLWD            -309754
#define PD_NOIAOSSS                    -309756
#define PD_NOIAOSSSACT                 -309758
#define PD_NOIACSSS                    -309760
#define PD_NOIACSSSACT                 -309762
#define PD_NOBBAOSSS                   -309764
#define PD_NOBBAOSSSACT                -309766
#define PD_NOBBACSSS                   -309768
#define PD_NOBBACSSSACT                -309770
#define PD_NOFIXSSS                    -309772
#define PD_NOFIXSSSACT                 -309774
#define PD_CREINCNOTALLWD              -309776
#define PD_TMPLCOMEMPTY                -309778
#define PD_NOFALLBSSS                  -309780
#define PD_NOFALLBSSSACT               -309782
#define PD_EXTINFSOURCEWRONG           -309784
#define PD_UNDERSCOREATEND             -309786
#define PD_RPTROWEMPTY                 -309788
#define PD_EXTPMLOGEMPTY               -309790
#define PD_EXTPOBLOGEMPTY              -309792
#define PD_EXTPOUTPLOGEMPTY            -309794
#define PD_EXTPPRCCALCEMPTY            -309796
#define PD_EXTPMSGVALEMPTY             -309798
#define PD_EXTPRECVALEMPTY             -309800
#define PD_EXTPOBEMPTY                 -309802
#define PD_EXTPMATCHEMPTY              -309804
#define PD_EXTPOBPROCEMPTY             -309806
#define PD_EXTPAUCHEMPTY               -309808
#define PD_EXTPCBCALCEMPTY             -309810
#define PD_EXTPSESSCHGEMPTY            -309812
#define PD_CBSIDEMPTY                  -309814
#define PD_TOFAGREEGRANEMPTY           -309816
#define PD_PGRIDEMPTY                  -309818
#define PD_NOPPL                       -309820
#define PD_NOPPLACT                    -309822
#define PD_PPLIDEMPTY                  -309824
#define PD_NOPLR                       -309826
#define PD_NOPLRACT                    -309828
#define PD_PLRIDEMPTY                  -309830
#define PD_REFTOPLR                    -309832
#define PD_BOTHPLRPRL                  -309834
#define PD_DOUBLEPLR                   -309836
#define PD_MAXQTYWRONG                 -309838
#define PD_MAXVALWRONG                 -309840
#define PD_MAXQTYEMPTY                 -309842
#define PD_MAXVALEMPTY                 -309844
#define PD_DOUBLEABT                   -309846
#define PD_NOTAUTHORIZEDINS            -309848
#define PD_NOOFADDSEREXCEED            -309850
#define PD_FEECOFFNOTALLWD             -309852
#define PD_EXTSETTLTYPEMPTY            -309854
#define PD_STARTRULESPEC               -309856
#define PD_ENDRULESPEC                 -309858
#define PD_NOENDWHNSTART               -309860
#define PD_LTDTOCLOSMATUR              -309862
#define PD_NOTTI                       -309864
#define PD_NOTTIACT                    -309866
#define PD_TTIIDEMPTY                  -309868
#define PD_REFTOTTI                    -309870
#define PD_REFTOMMP                    -309872
#define PD_NOMMP                       -309874
#define PD_INVQPROTVALUE               -309876
#define PD_INVDPROTVALUE               -309878
#define PD_QPROTVALUETOOLOW            -309880
#define PD_DPROTVALUETOOLOW            -309882
#define PD_INVINCLFUTURES              -309884
#define PD_RESUMENOTALLWD              -309886
#define PD_SUSPRESUMENOTALLWD          -309888
#define PD_LOGOUTNOTALLWD              -309890
#define PD_SETMAXLIMITNOTALLWD         -309892
#define PD_NODTI                       -309894
#define PD_NODTIACT                    -309896
#define PD_DTIIDEMPTY                  -309898
#define PD_NODFP                       -309900
#define PD_NODFPACT                    -309902
#define PD_DFPIDEMPTY                  -309904
#define PD_DOUBLEDFP                   -309906
#define PD_WRONGTIMEDELAY              -309908
#define PD_VOLATILITYEMPY              -309910
#define PD_INVMARMIN                   -309912
#define PD_MINSPREADGTMAX              -309914
#define PD_REFTOPGR                    -309916
#define PD_DWWRONGSUM                  -309918
#define PD_PCPOINTEXCEED               -309920
#define PD_NOPGR                       -309922
#define PD_NOPGRACT                    -309924
#define PD_NORSC                       -309926
#define PD_NORSCACT                    -309928
#define PD_RSCIDEMPTY                  -309930
#define PD_REFTORSC                    -309932
#define PD_PMAIDEMPTY                  -309934
#define PD_REFTOPMA                    -309936
#define PD_NOPMA                       -309938
#define PD_NOPMAACT                    -309940
#define PD_CFMIDEMPTY                  -309942
#define PD_REFTOCFM                    -309944
#define PD_NOCFM                       -309946
#define PD_NOCFMACT                    -309948
#define PD_PRCRVIDEMPTY                -309950
#define PD_DOUBCRVDEF                  -309952
#define PD_NOCRV                       -309954
#define PD_REFTOCRV                    -309956
#define PD_CRVIDEMPTY                  -309958
#define PD_NOCRVACT                    -309960
#define PD_NOCRDACT                    -309962
#define PD_NOPCO                       -309964
#define PD_REFTOPCO                    -309966
#define PD_PCOIDEMPTY                  -309968
#define PD_NOPCOACT                    -309970
#define PD_PCYRSEMPTY                  -309972
#define PD_DOUBLEPCO                   -309974
#define PD_NOUPPCCC                    -309976
#define PD_NOUPPCCCACT                 -309978
#define PD_OVERLPCNOTODD               -309980
#define PD_NOCCC                       -309982
#define PD_CIRCDEPCCCNOTALLOWED        -309984
#define PD_REFTOCCC                    -309986
#define PD_CCCIDEMPTY                  -309988
#define PD_NOCCCACT                    -309990
#define PD_MARGMETHEMPTY               -309992
#define PD_PC1NOMINORMAX               -309994
#define PD_PC2NOMINORMAX               -309996
#define PD_PC3NOMINORMAX               -309998
#define PD_STARTENDBOTHORNONE          -310000
#define PD_SHORTNUMEXCEEDED            -310002
#define PD_REFTOSTF                    -310004
#define PD_DERIVFROMEMPTY              -310006
#define PD_DOUBLESTF                   -310008
#define PD_NOTOP                       -310010
#define PD_NOTOPACT                    -310012
#define PD_REFTOTOP                    -310014
#define PD_TOPIDEMPTY                  -310016
#define PD_DOUBLETOL                   -310018
#define PD_TOLIDEMPTY                  -310020
#define PD_LISTTYPEEMPTY               -310022
#define PD_SORTITEMEMPTY               -310024
#define PD_NOTOL                       -310026
#define PD_REFTOTOL                    -310028
#define PD_LISTHDREMPTY                -310030
#define PD_EXPTIMENEG                  -310032
#define PD_FROZENTIMENEG               -310034
#define PD_MAXEXPLTMINEXP              -310036
#define PD_NOSTRKUPWHNCALIB            -310038
#define PD_NOSTRKDWNWHNCALIB           -310040
#define PD_NOSTRKEXTWHNCALIB           -310042
#define PD_NOMINEXPWHNCALIB            -310044
#define PD_NOMAXEXPWHNCALIB            -310046
#define PD_TTCBEMPTY                   -310048
#define PD_TTLEGEMPTY                  -310050
#define PD_REPOLTDISPASSED             -310052
#define PD_FROMTOLISTED                -310054
#define PD_NOSTA                       -310056
#define PD_NOSTAACT                    -310058
#define PD_STAIDEMPTY                  -310060
#define PD_DOUBLESTA                   -310062
#define PD_CSDEMPTY                    -310064
#define PD_CSDIDENTEMPTY               -310066
#define PD_NOEMB                       -310068
#define PD_NOEMBACT                    -310070
#define PD_EMBIDEMPTY                  -310072
#define PD_EXCMEMTYPEEMPTY             -310074
#define PD_DOUBLEEMB                   -310076
#define PD_REFTOEMB                    -310078
#define PD_REFTOSLC                    -310080
#define PD_NOPRSOURCEINS               -310082
#define PD_AUTOFIXEMPTY                -310084
#define PD_NOPRSOURCEINSACT            -310086
#define PD_NOMRG                       -310088
#define PD_NOMRGACT                    -310090
#define PD_NOFIX                       -310092
#define PD_MRGIDEMPTY                  -310094
#define PD_NOFIXACT                    -310096
#define PD_REFTOMRG                    -310098
#define PD_NOPPR                       -310100
#define PD_FIXIDEMPTY                  -310102
#define PD_NOPPRACT                    -310104
#define PD_DOUBLEFIX                   -310106
#define PD_PPRIDEMPTY                  -310108
#define PD_APPIDEMPTY                  -310110
#define PD_REFTOPPR                    -310112
#define PD_TARGCOMPEMPTY               -310114
#define PD_NODHG                       -310116
#define PD_PORTNUMEMPTY                -310118
#define PD_NODHGACT                    -310120
#define PD_FIXVEREMPTY                 -310122
#define PD_DHGIDEMPTY                  -310124
#define PD_CONNTYPEEMPTY               -310126
#define PD_REFTODHG                    -310128
#define PD_DROPFILTEREMPTY             -310130
#define PD_NOOMS                       -310132
#define PD_DROPFILTERNOTEMPTY          -310134
#define PD_NOOMSACT                    -310136
#define PD_DOUBLEULR                   -310138
#define PD_OMSIDEMPTY                  -310140
#define PD_USECOMPRWRONG               -310142
#define PD_REFTOOMS                    -310144
#define PD_RESETSEQWRONG               -310146
#define PD_NOEXR                       -310148
#define PD_WRONGABTATTR                -310150
#define PD_NOEXRACT                    -310152
#define PD_BOTHABTCLASS                -310154
#define PD_EXRIDEMPTY                  -310156
#define PD_SECIDEMPTY                  -310158
#define PD_REFTOEXR                    -310160
#define PD_ISINEMPTY                   -310162
#define PD_NOCCO                       -310164
#define PD_STFALREXISTS                -310166
#define PD_NOCCOACT                    -310168
#define PD_LONGFREEEMPTY               -310170
#define PD_CCOIDEMPTY                  -310172
#define PD_LISTDATEEMPTY               -310174
#define PD_REFTOCCO                    -310176
#define PD_ISSPRICEEMPTY               -310178
#define PD_NOCCG                       -310180
#define PD_NOITEMS                     -310182
#define PD_NOCCGACT                    -310184
#define PD_LONGINSEXIST                -310186
#define PD_CCGIDEMPTY                  -310188
#define PD_INSIDEXIST                  -310190
#define PD_REFTOCCG                    -310192
#define PD_NOTIE                       -310194
#define PD_NOTIEACT                    -310196
#define PD_TIEIDEMPTY                  -310198
#define PD_REFTOTIE                    -310200
#define PD_NOIRM                       -310202
#define PD_NOIRMACT                    -310204
#define PD_IRMIDEMPTY                  -310206
#define PD_REFTOIRM                    -310208
#define PD_NOWRM                       -310210
#define PD_NOWRMACT                    -310212
#define PD_WRMIDEMPTY                  -310214
#define PD_REFTOWRM                    -310216
#define PD_MINMATGTMAXMAT              -310218
#define PD_TIERNOEMPTY                 -310220
#define PD_DOUBLECCG                   -310222
#define PD_DATENUMBERNOTEMPTY          -310224
#define PD_MAXNUMBEREMPTY              -310226
#define PD_MAXDATEEMPTY                -310228
#define PD_NOTDPITEM                   -310230
#define PD_CCO1OR2EMPTY                -310232
#define PD_INVALIDVOLA                 -310234
#define PD_HIGHMAXEMPTY                -310236
#define PD_DAYSYEAREMPTY               -310238
#define PD_POINTSNOTODD                -310240
#define PD_PASSEDMAXDATE               -310242
#define PD_CIRCDEPWRMNOTALLOWED        -310244
#define PD_CCONOTCCG                   -310246
#define PD_POINTSPCNOTODD              -310248
#define PD_MAXDATENOTEMPTY             -310250
#define PD_CRERSKFILEEMPTY             -310252
#define PD_CREVECFILEEMPTY             -310254
#define PD_DOUBLEMRG                   -310256
#define PD_DISCMETHEMPTY               -310258
#define PD_NOCURVDEFITEM               -310260
#define PD_PRIONOTZERO                 -310262
#define PD_PRADOUBLEDEF                -310264
#define PD_PRAOTHERINT                 -310266
#define PD_PRACODEEXIST                -310268
#define PD_PRAINTINMARKET              -310270
#define PD_PRANOCODE                   -310272
#define PD_NOPRA                       -310274
#define PD_NOPRAACT                    -310276
#define PD_PRAIDEMPTY                  -310278
#define PD_REFTOPRA                    -310280
#define PD_PRAOTHERMAR                 -310282
#define PD_PRADESCRNOTUNIQUE           -310284
#define PD_PRACODENOTUNIQUE            -310286
#define PD_PUBYLDCRVEMPTY              -310288
#define PD_CRERSKCUBEMPTY              -310290
#define PD_INTRTYPENOTRIGHT            -310292
#define PD_MONTHLYSETTLNOTALLWD        -310294
#define PD_STRESSMARGCALCEMPTY         -310296
#define PD_STRESSMARGNOTCONSEC         -310298
#define PD_BASESCENEMPTY               -310300
#define PD_BASESCENNOTCONSEC           -310302
#define PD_CALCSTRESSNOTNEG            -310304
#define PD_PRANOTUNIQUE                -310306
#define PD_MARSCENEMPTY                -310308
#define PD_MARSCENNOTCONSEC            -310310
#define PD_INVSLCCOM                   -310312
#define PD_NOREFIXSTART                -310314
#define PD_NOREFIXCPN                  -310316
#define PD_ADDDIVNOTALLWD              -310318
#define PD_NOPDH                       -310320
#define PD_NOPDHACT                    -310322
#define PD_PDHIDEMPTY                  -310324
#define PD_REFTOPDH                    -310326
#define PD_NORSG                       -310328
#define PD_NORSGACT                    -310330
#define PD_RSGIDEMPTY                  -310332
#define PD_REFTORSG                    -310334
#define PD_NOSRG                       -310336
#define PD_NOSRGACT                    -310338
#define PD_SRGIDEMPTY                  -310340
#define PD_REFTOSRG                    -310342
#define PD_PDWWRONGSUM                 -310344
#define PD_SIZEMINGTMAX                -310346
#define PD_PCSIDEMPTY                  -310348
#define PD_DOUBLEPCS                   -310350
#define PD_MORETHANONEPCS              -310352
#define PD_NOPCS                       -310354
#define PD_NOPCSACT                    -310356
#define PD_CONTRELIGPCSEMPTY           -310358
#define PD_SUPERPRODAREAIDNOTUNIQUE    -310360
#define PD_REFTOPCS                    -310362
#define PD_NOHKP                       -310364
#define PD_NOHKPACT                    -310366
#define PD_HKPIDEMPTY                  -310368
#define PD_DELDAYSNOTZERO              -310370
#define PD_TIERDOUBLE                  -310372
#define PD_CREDITRATETOLARGE           -310374
#define PD_MARGDAYSEMPTY               -310376
#define PD_FIXTRRTYPEEMPTY             -310378
#define PD_BALANCEANDSTRICTEMPTY       -310380
#define PD_BALANCEACCEMPTY             -310382
#define PD_ONESYSTEMCLHALLOWED         -310384
#define PD_ISSNOTCLEARING              -310386
#define PD_ISSCONVNOTEQ                -310388
#define PD_PRCMETHEMPTY                -310390
#define PD_TOPNOTADDED                 -310392
#define PD_EPCALCRULEEMPTY             -310394
#define PD_NOTACCARPRA                 -310396
#define PD_NOIFFTDNTD                  -310398
#define PD_NOIFDLVSTARTNTD             -310400
#define PD_NOIFDLVSTOPNTD              -310402
#define PD_NOIFSTARTNTD                -310404
#define PD_NOIFSTOPNTD                 -310406
#define PD_INVALIDACTTIME              -310408
#define PD_DELIVSTARTAFTERSTOP         -310410
#define PD_USRIDWRONGCHAR              -310412
#define PD_MARCRVEMPTY                 -310414
#define PD_MARCRVFILLEDIN              -310416
#define PD_MARSECCRVFORW               -310418
#define PD_CRVTENOREMPTY               -310420
#define PD_DISCCRVNOTEMPTY             -310422
#define PD_DISCCRVEMPTY                -310424
#define PD_DISCCRVNOTDISC              -310426
#define PD_MARVALBASEEMPTY             -310428
#define PD_CRVTYPEEMPTY                -310430
#define PD_NOINTRINS                   -310432
#define PD_NOINTRINSACT                -310434
#define PD_NOSPONSCST                  -310436
#define PD_NOSPONSCSTACT               -310438
#define PD_SPONSCSTEMPTY               -310440
#define PD_SPONSEXCEMPTY               -310442
#define PD_NOSPONSCLICST               -310444
#define PD_NOSPONSCLICSTACT            -310446
#define PD_SPONSCLICSTEMPTY            -310448
#define PD_SPONSCLIEXCEMPTY            -310450
#define PD_SPONSCLIALRINPTL            -310452
#define PD_USRALRINPTL                 -310454
#define PD_RISKPROFILEPARAMEMPTY       -310456
#define PD_USRWRONGCST                 -310458
#define PD_PTLIDEMPTY                  -310460
#define PD_REFTOPTL                    -310462
#define PD_NOPTL                       -310464
#define PD_DOUBLEUSER                  -310466
#define PD_SGSIDEMPTY                  -310468
#define PD_REFTOSGS                    -310470
#define PD_NOSGS                       -310472
#define PD_NOSGSACT                    -310474
#define PD_DOUBLESGS                   -310476
#define PD_SHRTSRUSPSIDEMPTY           -310478
#define PD_SHRTLENEMPTY                -310480
#define PD_REFTORMS                    -310482
#define PD_SCALEFACEMPTY               -310484
#define PD_RMSIDEMPTY                  -310486
#define PD_NORMS                       -310488
#define PD_MARSECCRVEMPTY              -310490
#define PD_NODEPINS                    -310492
#define PD_NODEPINSACT                 -310494
#define PD_DEPINSEMPTY                 -310496
#define PD_DEPINSNOTEMPTY              -310498
#define PD_CONSTRMETHWRONG             -310500
#define PD_CRVTENORNOTEMPTY            -310502
#define PD_DEPINSNOTDEPOSIT            -310504
#define PD_FORWARDSTARTNOTEMPTY        -310506
#define PD_FORWARDSTARTLENZERO         -310508
#define PD_OISWRONG                    -310510
#define PD_NOTINTEGERYEARDAYS          -310512
#define PD_BOTHOTCENDANDSEPMARVAL      -310514
#define PD_CRVFORW                     -310516
#define PD_KFDIDEMPTY                  -310518
#define PD_REFTOKFD                    -310520
#define PD_NOKFD                       -310522
#define PD_NOKFDACT                    -310524
#define PD_KFNIDEMPTY                  -310526
#define PD_NOKFN                       -310528
#define PD_NOKFNACT                    -310530
#define PD_DOUBLEFOOTNOTE              -310532
#define PD_KOIIDEMPTY                  -310534
#define PD_NOKOI                       -310536
#define PD_NOKOIACT                    -310538
#define PD_DOUBLEOPENPERIOD            -310540
#define PD_INVALIDDATE                 -310542
#define PD_INVALIDFIRSTRESET           -310544
#define PD_INVALIDFIRSTFIX1            -310546
#define PD_INVALIDRESET1               -310548
#define PD_INVALIDFIRSTFIX2            -310550
#define PD_INVALIDRESET2               -310552
#define PD_INVALIDFIRSTFIX3            -310554
#define PD_INVALIDRESET3               -310556
#define PD_INVALIDFIRSTFIX4            -310558
#define PD_INVALIDRESET4               -310560
#define PD_COHIDEMPTY                  -310562
#define PD_NOCOH                       -310564
#define PD_NOCOHACT                    -310566
#define PD_REFTOCOH                    -310568
#define PD_ACCEPTCOLLEMPTY             -310570
#define PD_ALLOWCOLLEMPTY              -310572
#define PD_DOUBLETIMETOMAT             -310574
#define PD_REFTOHCT                    -310576
#define PD_ACCTTYPEEMPTY               -310578
#define PD_PTNIDEMPTY                  -310580
#define PD_NOPTN                       -310582
#define PD_NOPTNACT                    -310584
#define PD_DOUBLEPTN                   -310586
#define PD_EMAILEMPTY                  -310588
#define PD_UNITISEMPTY                 -310590
#define PD_SPONSUSEREMPTY              -310592
#define PD_NOSPONSUSR                  -310594
#define PD_NOSPONSUSRACT               -310596
#define PD_WRONGSPONSUSR               -310598
#define PD_WRONGUNIT                   -310600
#define PD_NOCRW                       -310602
#define PD_SPONSNOTAUTH                -310604
#define PD_DELPTNNOTALLWD              -310606
#define PD_DELPTUNOTALLWD              -310608
#define PD_DELPTPNOTALLWD              -310610
#define PD_DELPTLNOTALLWD              -310612
#define PD_SPONSNOTTHESAME             -310614
#define PD_REFTOCRW                    -310616
#define PD_CRWIDEMPTY                  -310618
#define PD_NOCRWACT                    -310620
#define PD_ILLPRLIMSUP                 -310622
#define PD_ILLPRLIMSUPTYPE             -310624
#define PD_FROMPRICEDIFF               -310626
#define PD_NORPS                       -310628
#define PD_NORPSACT                    -310630
#define PD_RPSIDEMPTY                  -310632
#define PD_REFTORPS                    -310634
#define PD_PRICESOURCEEMPTY            -310636
#define PD_DOUBLERPS                   -310638
#define PD_NODYNPLR                    -310640
#define PD_NODYNPLRACT                 -310642
#define PD_DYNPLRIDEMPTY               -310644
#define PD_NODYNRPS                    -310646
#define PD_NODYNRPSACT                 -310648
#define PD_PLRWRONGDEF                 -310650
#define PD_SPONSUSRCHANGED             -310652
#define PD_ENAWARNCHANGED              -310654
#define PD_ENANOTCHANGED               -310656
#define PD_ENABRCHANGED                -310658
#define PD_ADDPTUNOTALLWD              -310660
#define PD_ADDPTPNOTALLWD              -310662
#define PD_LCOUPONEMPTY                -310664
#define PD_DAYCALCEMPTY                -310666
#define PD_DAYCALCWRONG                -310668
#define PD_ISSCURIDEMPTY               -310670
#define PD_NOISSCUR                    -310672
#define PD_FLOATFIXEDEMPTY             -310674
#define PD_FLOATFIXEDWRONG             -310676
#define PD_GWCIDEMPTY                  -310678
#define PD_PRIKEYEMPTY                 -310680
#define PD_VALUEEMPTY                  -310682
#define PD_GWCDUPLICATE                -310684
#define PD_NOGWC                       -310686
#define PD_NOGWCACT                    -310688
#define PD_TMPLINCIDEMPTY              -310690
#define PD_WRONGTEMPL                  -310692
#define PD_RICCODEEMPTY                -310694
#define PD_PTLIDWRONG                  -310696
#define PD_PTPUNITCHANGED              -310698
#define PD_COLLHANDLWRONG              -310700
#define PD_REFTOVCU                    -310702
#define PD_VCUIDEMPTY                  -310704
#define PD_NOVCU                       -310706
#define PD_NOVCUACT                    -310708
#define PD_DOUBLEVCU                   -310710
#define PD_RPSMUSTBESAME               -310712
#define PD_UNITVALNOTALLWD             -310714
#define PD_NOKIV                       -310716
#define PD_NOKTR                       -310718
#define PD_INVALIDREPAYM1              -310720
#define PD_INVALIDREPAYM2              -310722
#define PD_INVALIDREPAYM3              -310724
#define PD_INVALIDREPAYM4              -310726
#define PD_KIVIDEMPTY                  -310728
#define PD_INDEXDATEEMPTY              -310730
#define PD_INDEXDATENOTUNIQUE          -310732
#define PD_KTRIDEMPTY                  -310734
#define PD_TAXTYPEEMPTY                -310736
#define PD_CSHFLOWSTSEMPTY             -310738
#define PD_CONVCODEEMPTY               -310740
#define PD_TAXEMPTY                    -310742
#define PD_LOANTYPEEMPTY               -310744
#define PD_REPAYMPROFEMPTY             -310746
#define PD_REPAYMPROFSPECEMPTY         -310748
#define PD_PRINCIXLINKEMPTY            -310750
#define PD_CUPTYPEEMPTY                -310752
#define PD_BONDTYPEEMPTY               -310754
#define PD_FIRSTISSDATEEMPTY           -310756
#define PD_ISSUERTYPEEMPTY             -310758
#define PD_SECPLACEMEMPTY              -310760
#define PD_YIELDAVRGREMPTY             -310762
#define PD_TURNOVRGREMPTY              -310764
#define PD_GOVGUAREMPTY                -310766
#define PD_INVALIDREPAYM5              -310768
#define PD_INVALIDREPAYM6              -310770
#define PD_INVALIDREPAYM7              -310772
#define PD_INVALIDREPAYM8              -310774
#define PD_INVALIDREPAYM9              -310776
#define PD_INVALIDREPAYM10             -310778
#define PD_INVALIDREPAYM11             -310780
#define PD_INVALIDREPAYM12             -310782
#define PD_CASHFLOWNOTNO               -310784
#define PD_YIELDCALCNOTNO              -310786
#define PD_DRAWPRICEEMPTY              -310788
#define PD_NOOFOPENPEREMPTY            -310790
#define PD_LASTDUEDATEEMPTY            -310792
#define PD_DRAWPRICEWRONG              -310794
#define PD_TURNOVRGRNOTTR              -310796
#define PD_COUPONTYPEWRONG             -310798
#define PD_TURNOVRGRTR                 -310800
#define PD_REPAYMPROFSPECWRONG         -310802
#define PD_DRAWPRICENOTEMPTY           -310804
#define PD_INTRSBASESPRNOTEMPTY        -310806
#define PD_FLOATDATENOTEMPTY           -310808
#define PD_FLOATDATEEMPTY              -310810
#define PD_INTRSBASECAPEMPTY           -310812
#define PD_INTRSBASECAPNOTEMPTY        -310814
#define PD_CIBORSTRIKENOTEMPTY         -310816
#define PD_FIRSTINTPAYMYWRONG          -310818
#define PD_INTRSBASESPREMPTY           -310820
#define PD_FIRSTISSAFTLAST             -310822
#define PD_OPENPERGTDURINY             -310824
#define PD_LOANTYPEINFOSPEC            -310826
#define PD_OPENPEREMPTY                -310828
#define PD_NEWISSNOMEMPTY              -310830
#define PD_FIRSTOPENEMPTY              -310832
#define PD_LASTOPENEMPTY               -310834
#define PD_INTDEBTPRICEEMPTY           -310836
#define PD_INTDEBTPRICENOTEMPTY        -310838
#define PD_INTDEBTRATEEMPTY            -310840
#define PD_INTDEBTRATENOTEMPTY         -310842
#define PD_SERIALLOANRATIOEMPTY        -310844
#define PD_SERIALLOANRATIONOTEMPTY     -310846
#define PD_SERIALLOANNOREPEMPTY        -310848
#define PD_SERIALLOANNOREPNOTEMPTY     -310850
#define PD_BULLETLOANNOREPEMPTY        -310852
#define PD_BULLETLOANNOREPNOTEMPTY     -310854
#define PD_DRAWINGDATEEMPTY            -310856
#define PD_DRAWINGDATENOTEMPTY         -310858
#define PD_FIRSTDEBTSETTLDATEEMPTY     -310860
#define PD_FIRSTDEBTSETTLDATENOTEMPTY  -310862
#define PD_PUBLDATEEMPTY               -310864
#define PD_PUBLDATENOTEMPTY            -310866
#define PD_NOOFDEFERREDWRONG           -310868
#define PD_CALLPRICEEMPTY              -310870
#define PD_YIELDCALCNOTYES             -310872
#define PD_BONDTYPEWRONG               -310874
#define PD_LASTISSDATEEMPTY            -310876
#define PD_CALCDATEEMPTY               -310878
#define PD_COUPREPAYMDATEEMPTY         -310880
#define PD_FIRSTAFTLAST                -310882
#define PD_LASTAFTCALC                 -310884
#define PD_CALCAFTDRAW                 -310886
#define PD_DRAWAFTPUBL                 -310888
#define PD_PUBLAFTCUPREPAYM            -310890
#define PD_FIRSTISSUENOTINCR           -310892
#define PD_LASTISSUENOTINCR            -310894
#define PD_CALCNOTINCR                 -310896
#define PD_DRAWNOTINCR                 -310898
#define PD_PUBLNOTINCR                 -310900
#define PD_REPAYMNOTINCR               -310902
#define PD_INCIDEXIST                  -310904
#define PD_INSIDEXISTFROMUND           -310906
#define PD_FIRSTTRADEDATEEMPTY         -310908
#define PD_TRADINGUNITEMPTY            -310910
#define PD_DAYSXCOUPONWRONG            -310912
#define PD_PTLUSREMPTY                 -310914
#define PD_MAXLIMITEXCEEDED            -310916
#define PD_FXMIDEMPTY                  -310918
#define PD_NOFXM                       -310920
#define PD_NOFXMACT                    -310922
#define PD_NOFXINT                     -310924
#define PD_NOFXINTACT                  -310926
#define PD_NOGBLCUR                    -310928
#define PD_NOGBLCURACT                 -310930
#define PD_NOPRHOLDINT                 -310932
#define PD_NOPRHOLDINTACT              -310934
#define PD_PERCENTILEWRONG             -310936
#define PD_REFTOFXM                    -310938
#define PD_PFGIDEMPTY                  -310940
#define PD_ATGIDEMPTY                  -310942
#define PD_NOATG                       -310944
#define PD_NOATGACT                    -310946
#define PD_REFTOATG                    -310948
#define PD_DOUBLEATG                   -310950
#define PD_ACCUMLVLEMPTY               -310952
#define PD_PRODAGGRLVLEMPTY            -310954
#define PD_PRODEFFLVLEMPTY             -310956
#define PD_LEVELEMPTY                  -310958
#define PD_LOWERLIMITEMPTY             -310960
#define PD_UPPERLIMITEMPTY             -310962
#define PD_ACCUMBASEEMPTY              -310964
#define PD_ACCUMPEREMPTY               -310966
#define PD_EFFECTAFTIDEMPTY            -310968
#define PD_EFFDUREMPTY                 -310970
#define PD_DOUBLEPFT                   -310972
#define PD_DOUBLELEVEL                 -310974
#define PD_REFTOPFG                    -310976
#define PD_NOPFG                       -310978
#define PD_NOPFTITEMS                  -310980
#define PD_NOPFGLADDER                 -310982
#define PD_INSTRDATEEMPTY              -310984
#define PD_RPGISCONNECTED              -310986
#define PD_DEFUSRALRINPTL              -310988
#define PD_ENADEFUSRCHANGED            -310990
#define PD_LINKEDISSAME                -310992
#define PD_LINKEDISLINKED              -310994
#define PD_CISISLINKED                 -310996
#define PD_MAXPTLUSREXCEEDED           -310998
#define PD_MAXPTLPTPEXCEEDED           -311000
#define PD_MAXPTNEXCEEDED              -311002
#define PD_LONGUNDTOOLONG              -311004
#define PD_TIMEVALUEBASEEMPTY          -311006
#define PD_SPOTDELAYTYPEEMPTY          -311008
#define PD_STARTOFMARGINPEREMPTY       -311010
#define PD_MTMSTYLEEMPTY               -311012
#define PD_PCGIDEMPTY                  -311014
#define PD_NOPCG                       -311016
#define PD_NOPCGACT                    -311018
#define PD_REFTOPCG                    -311020
#define PD_DOUBLEPCG                   -311022
#define PD_STRIDEMPTY                  -311024
#define PD_NOSTR                       -311026
#define PD_NOSTRACT                    -311028
#define PD_REFTOSTR                    -311030
#define PD_NOOFINSEMPTY                -311032
#define PD_STRIPRANGEEMPTY             -311034
#define PD_SPLITRULEEMPTY              -311036
#define PD_RISKTYPEEMPTY               -311038
#define PD_PCYIDEMPTY                  -311040
#define PD_NOPCY                       -311042
#define PD_NOPCYACT                    -311044
#define PD_REFTOPCY                    -311046
#define PD_DOUBLEPCY                   -311048
#define PD_NOHEACST                    -311050
#define PD_NOHEACSTACT                 -311052
#define PD_NOCRGCST                    -311054
#define PD_NOCRGCSTACT                 -311056
#define PD_NOCPYEXC                    -311058
#define PD_NOCPYEXCACT                 -311060
#define PD_CISISFULL                   -311062
#define PD_FXCIDEMPTY                  -311064
#define PD_NOFXC                       -311066
#define PD_NOFXCACT                    -311068
#define PD_REFTOFXC                    -311070
#define PD_TENIDEMPTY                  -311072
#define PD_NOTEN                       -311074
#define PD_NOTENACT                    -311076
#define PD_TENORTYPEEMPTY              -311078
#define PD_DOUBLETEN                   -311080
#define PD_DOUBLECUR                   -311082
#define PD_FTPNOPWD                    -311084
#define PD_EOTIFADJONLYDAILY           -311086
#define PD_STARTSTOPFROMUPPER          -311088
#define PD_USEFTDREFONLYDAILY          -311090
#define PD_EXPCLOSED                   -311092
#define PD_ONLYCALDAYSWITHUNITMONTH    -311094
#define PD_NOAREACOM                   -311096
#define PD_NOAREACOMACT                -311098
#define PD_AREACOMIDEMPTY              -311100
#define PD_NOSYSTEMCOM                 -311102
#define PD_NOSYSTEMCOMACT              -311104
#define PD_SYSTEMCOMIDEMPTY            -311106
#define PD_NOEPA                       -311108
#define PD_REFTOEPA                    -311110
#define PD_PENDINGNOTALLWD             -311112
#define PD_NOIXC                       -311114
#define PD_IXCIDEMPTY                  -311116
#define PD_INDEXINSIDEMPTY             -311118
#define PD_NOIDXINS                    -311120
#define PD_NOIDXINSACT                 -311122
#define PD_INDEXALREXIST               -311124
#define PD_REFTOIXC                    -311126
#define PD_ICFIDEMPTY                  -311128
#define PD_NOICF                       -311130
#define PD_NOICFACT                    -311132
#define PD_MSEIDEMPTY                  -311134
#define PD_MSECODEEMPTY                -311136
#define PD_NOMSE                       -311138
#define PD_NOMSEACT                    -311140
#define PD_EXTFULLHOLDBWRONG           -311142
#define PD_PRICESOURCESAME             -311144
#define PD_PRICESOURCEISLINKED         -311146
#define PD_ONLYONELOTALLOWED           -311148
#define PD_ONLYROUNDLOTALLOWED         -311150
#define PD_INSISLINKED                 -311152
#define PD_SPREADTOLEMPTY              -311154
#define PD_LTPTOLEMPTY                 -311156
#define PD_PRICESOURCEDIFFUNDERLYING   -311158
#define PD_NOIOC                       -311160
#define PD_NOIOCACT                    -311162
#define PD_IOCIDEMPTY                  -311164
#define PD_DOUBLEIOC                   -311166
#define PD_PROTOCOLEMPTY               -311168
#define PD_PROTOCOLNOTEMPTY            -311170
#define PD_MULTICASTEMPTY              -311172
#define PD_MULTICASTNOTEMPTY           -311174
#define PD_FAMILYNAMEEMPTY             -311176
#define PD_PRIMARYNODEEMPTY            -311178
#define PD_PRIMARYINSTEMPTY            -311180
#define PD_STANDBYNODEEMPTY            -311182
#define PD_STANDBYINSTEMPTY            -311184
#define PD_NOOCG                       -311186
#define PD_NOOCGACT                    -311188
#define PD_PRIMARYNODEEXIST            -311190
#define PD_STANDBYNODEEXIST            -311192
#define PD_REFTOIOC                    -311194
#define PD_STANDBYSAMEASPRIMARY        -311196
#define PD_PRIMARYBADPAIR              -311198
#define PD_STANDBYBADPAIR              -311200
#define PD_ONLYONEDEFIOC               -311202
#define PD_WRONGPORTNUMBER             -311204
#define PD_PORTNOTUNIQUE               -311206
#define PD_APPLIDNOTUNIQUE             -311208
#define PD_DOUBLEAPPL                  -311210
#define PD_FREEFLOATGTSHAREDISSUES     -311212
#define PD_FREEFLOATRATIOTOLARGE       -311214
#define PD_FREEFLOATSHARESZERO         -311216
#define PD_FREEFLOATZERO               -311218
#define PD_DELIVSERIENOTCLEARED        -311220
#define PD_NODELIVINS                  -311222
#define PD_NODELIVINSACT               -311224
#define PD_STRIPMONTHNOTACT            -311226
#define PD_NOGBLCRVCUR                 -311228
#define PD_NOGBLCRVCURACT              -311230
#define PD_SUBMETHODMARGEMPTY          -311232
#define PD_LAMBDAWEIGHTEDWRONG         -311234
#define PD_LAMBDAEQUALWRONG            -311236
#define PD_MAXNUMBERTOSMALL            -311238
#define PD_RANKINGACCCALCWRONG         -311240
#define PD_TOTACCCALCTOBIG             -311242
#define PD_SUBMETHODCCAREMPTY          -311244
#define PD_RANKINGNOTALLLOWED          -311246
#define PD_LAMBDANOTALLOWED            -311248
#define PD_REFTOPQC                    -311250
#define PD_KNOCKSTYLESPEC              -311252
#define PD_PQCANDLSTIDEMPTY            -311254
#define PD_PQCANDLSTIDSPEC             -311256
#define PD_MINVOLPQRNOTEMPTY           -311258
#define PD_MINVOLPQREMPTY              -311260
#define PD_ECLIDEMPTY                  -311262
#define PD_REFTOECL                    -311264
#define PD_NOECL                       -311266
#define PD_DELECLNOTALLWD              -311268
#define PD_MISSINGCONFIG               -311270
#define PD_WRONGCONFIGVAL              -311272
#define PD_UNITDIFFERFROMEXC           -311274
#define PD_NOTEQUITYINDEX              -311276
#define PD_MAXCHGEMPTY                 -311278
#define PD_WRLIDEMPTY                  -311280
#define PD_NOWRL                       -311282
#define PD_NOWRLACT                    -311284
#define PD_REFTOWRL                    -311286
#define PD_NOSIS                       -311288
#define PD_NOSISACT                    -311290
#define PD_SISIDEMPTY                  -311292
#define PD_REFTOSIS                    -311294
#define PD_SISTIMEEMPTY                -311296
#define PD_CHAEMPTY                    -311298
#define PD_DOUBLESISTIME               -311300
#define PD_DOUBLECLA                   -311302
#define PD_NOPFC                       -311304
#define PD_NOPFCACT                    -311306
#define PD_NOINH                       -311308
#define PD_NOINHACT                    -311310
#define PD_NOREF                       -311312
#define PD_NOREFACT                    -311314
#define PD_PFCIDEMPTY                  -311316
#define PD_PENCOMP                     -311318
#define PD_INHIDEMPTY                  -311320
#define PD_REFIDEMPTY                  -311322
#define PD_REFTOINH                    -311324
#define PD_DOUBLEINH                   -311326
#define PD_REFTOREF                    -311328
#define PD_DOUBLEREF                   -311330
#define PD_REFTOPFC                    -311332
#define PD_DOUBLEPFC                   -311334
#define PD_STARTTIME                   -311336
#define PD_ENDTIME                     -311338
#define PD_OFFSETNUMBER                -311340
#define PD_STARTTIMEGREATENDTIME       -311342
#define PD_NOESP                       -311344
#define PD_NOESPACT                    -311346
#define PD_REFTOESP                    -311348
#define PD_ESPIDEMPTY                  -311350
#define PD_NOCSE                       -311352
#define PD_NOCSEACT                    -311354
#define PD_NODEFCSE                    -311356
#define PD_NODEFCSEACT                 -311358
#define PD_CSEIDEMPTY                  -311360
#define PD_FROMTIMEEMPTY               -311362
#define PD_REFTOCSE                    -311364
#define PD_DOUBLECSETIME               -311366
#define PD_STARTDATEGREATERENDDATE     -311368
#define PD_NOHSE                       -311370
#define PD_NOHSEACT                    -311372
#define PD_HSEIDEMPTY                  -311374
#define PD_REFTOHSE                    -311376
#define PD_DEFCSEORRECORD              -311378
#define PD_SHARESOP                    -311380
#define PD_FREEFLOATOP                 -311382
#define PD_MIDMINMAX                   -311384
#define PD_MIDPOINTTRADESINFO          -311386
#define PD_EXTSETTLPARAM               -311388
#define PD_NOCLG                       -311390
#define PD_NOCLGACT                    -311392
#define PD_CLGIDEMPTY                  -311394
#define PD_VAGLIMIT                    -311396
#define PD_INDSECURLIMIT               -311398
#define PD_REFTOCLG                    -311400
#define PD_DOUBLECLG                   -311402
#define PD_NODFU                       -311404
#define PD_NODFUACT                    -311406
#define PD_NOPCC                       -311408
#define PD_NOPCCACT                    -311410
#define PD_DFUIDEMPTY                  -311412
#define PD_PCCIDEMPTY                  -311414
#define PD_REFTODFU                    -311416
#define PD_REFTOPCC                    -311418
#define PD_DOUBLERRDID                 -311420
#define PD_STRKOREXPCHANGED            -311422
#define PD_NEWSTRKNOTALLWD             -311424
#define PD_NEWSTRKNOTSPEC              -311426
#define PD_NEWEXPNOTALLWD              -311428
#define PD_NEWEXPNOTSPEC               -311430
#define PD_SOSTRKNOTALLWD              -311432
#define PD_SOSTRKNOTSPEC               -311434
#define PD_SOEXPNOTALLWD               -311436
#define PD_SOEXPNOTSPEC                -311438
#define PD_UPDISSNOTALLWD              -311440
#define PD_NOTARRP                     -311442
#define PD_NOTARRPACT                  -311444
#define PD_CLONEFEEISWRONG             -311446
#define PD_STRKPROPWRONG               -311448
#define PD_DEALPROPWRONG               -311450
#define PD_CONTRSZOPWRONG              -311452
#define PD_PRCQUOTOPWRONG              -311454
#define PD_CONTROPWRONG                -311456
#define PD_UNDPROPWRONG                -311458
#define PD_UNDMARGPROPWRONG            -311460
#define PD_CONSTCONTRWRONG             -311462
#define PD_INHISINWRONG                -311464
#define PD_ADJSAMEISWRONG              -311466
#define PD_PRINFOPREVDAYWRONG          -311468
#define PD_NOOFSHARESOPWRONG           -311470
#define PD_FREEFLOATOPWRONG            -311472
#define PD_ISNEWWRONG                  -311474
#define PD_ISSPINOFFWRONG              -311476
#define PD_SOMODIFIERWRONG             -311478
#define PD_EXPDATEOPWRONG              -311480
#define PD_MOVETRDSTATWRONG            -311482
#define PD_DOUBLEOLDINSID              -311484
#define PD_NOCMCST                     -311486
#define PD_NOCMCSTACT                  -311488
#define PD_LEGINSTNOTINCM              -311490
#define PD_NOCMFORTRADEONCM            -311492
#define PD_SETTLAFTEREXP               -311494
#define PD_SETTLAFTEREFFEXP            -311496
#define PD_SETTLBEFLASTTRAD            -311498
#define PD_BOTHFROMPANDFROMT           -311500
#define PD_PDLFILLALL                  -311502
#define PD_NOETP                       -311504
#define PD_NOETPACT                    -311506
#define PD_REFTOETP                    -311508
#define PD_ETPIDEMPTY                  -311510
#define PD_ETPRPLRIDEMPTY              -311512
#define PD_NOPRETRADEVALIDATION        -311514
#define PD_PTCIDEMPTY                  -311516
#define PD_NOPTC                       -311518
#define PD_NOPTCACT                    -311520
#define PD_DOUBLEPTC                   -311522
#define PD_REFTOPTC                    -311524
#define PD_PTLEMAILDIFF                -311526
#define PD_PTCIDIFF                    -311528
#define PD_NETTEDCONSCHANGED           -311530
#define PD_DELPTCNOTALLWD              -311532
#define PD_OPTLONGCOEFFCHANGED         -311534
#define PD_OPTSHORTCOEFFCHANGED        -311536
#define PD_FUTCOEFFCHANGED             -311538
#define PD_OPTLONGCOEFFWRONG           -311540
#define PD_OPTSHORTCOEFFWRONG          -311542
#define PD_FUTCOEFFWRONG               -311544
#define PD_MAXPTCEXCEEDED              -311546
#define PD_SPONSCLINOTEMPTY            -311548
#define PD_PTLUSRNOTEMPTY              -311550
#define PD_LASTTRIGGEREMPTY            -311552
#define PD_TIERNOTSPEC                 -311554
#define PD_TIER2EMPTY                  -311556
#define PD_TIER3EMPTY                  -311558
#define PD_NOCOMTIER1                  -311560
#define PD_NOCOMTIER2                  -311562
#define PD_NOCOMTIER3                  -311564
#define PD_NOCOMTIER4                  -311566
#define PD_REFCOMTIER                  -311568
#define PD_TSPIDEMPTY                  -311570
#define PD_NOTSP                       -311572
#define PD_NOTSPACT                    -311574
#define PD_DOUBLETSP                   -311576
#define PD_STARTTIMEEMPTY              -311578
#define PD_NOREFINC                    -311580
#define PD_NOREFINCACT                 -311582
#define PD_REFINCEMPTY                 -311584
#define PD_TARINDEMPTY                 -311586
#define PD_REQFULFILRESPRANGE          -311588
#define PD_ACTORDEMPTY                 -311590
#define PD_NEWORDEMPTY                 -311592
#define PD_DFCIDEMPTY                  -311594
#define PD_DEPOSITTIMEWRONG            -311596
#define PD_WITHDRAWALTIMEWRONG         -311598
#define PD_TRANSFERTIMEWRONG           -311600
#define PD_EXPDATEEXCEEDMAX            -311602
#define PD_STARTDEPOSITEMPTY           -311604
#define PD_ENDDEPOSITEMPTY             -311606
#define PD_STARTWITHDREMPTY            -311608
#define PD_ENDWITHDREMPTY              -311610
#define PD_STARTTRANSFEREMPTY          -311612
#define PD_ENDTRANSFEREMPTY            -311614
#define PD_DFUSIZEEMPTY                -311616
#define PD_DFUUNITEMPTY                -311618
#define PD_DPANDMTNOTALLOWED           -311620
#define PD_DPDUPLICATE                 -311622
#define PD_NODFC                       -311624
#define PD_NODFCACT                    -311626
#define PD_REFTODFC                    -311628
#define PD_MONTHEMPTY                  -311630
#define PD_DOUBLEDATE                  -311632
#define PD_NOCONTRDFU1                 -311634
#define PD_NOCONTRDFU1ACT              -311636
#define PD_NOCONTRDFU2                 -311638
#define PD_NOCONTRDFU2ACT              -311640
#define PD_NOTIFICATIONTOLARGE         -311642
#define PD_CALCPERIODEMPTY             -311644
#define PD_CALCPERIODSPECIFIED         -311646
#define PD_SPECIFICDATEEMPTY           -311648
#define PD_SPECIFICDATESPECIFIED       -311650
#define PD_SPECIFICDATEPASSED          -311652
#define PD_CONTRIBCALENDAREMPTY        -311654
#define PD_DAYTOLARGE                  -311656
#define PD_CONTRIBCALENDARNOTEMPTY     -311658
#define PD_BOTHDATEANDCALENDAR         -311660
#define PD_DFUTYPEEMPTY                -311662
#define PD_LOSSCONNECTEDASDFU          -311664
#define PD_DFUCONNECTEDASLOSS          -311666
#define PD_MARGINSOURCEEMPTY           -311668
#define PD_MMPROTVALUETOOHIGH          -311670
#define PD_OTHERACTIVATION             -311672
#define PD_STRIKEISNEG                 -311674
#define PD_COUNTERSIGNWRONG            -311676
#define PD_REFTOCSD                    -311678
#define PD_CSDIDEMPTY                  -311680
#define PD_NOCSD                       -311682
#define PD_NOCSDACT                    -311684
#define PD_COLLTRANSEMPTY              -311686
#define PD_DOUBLECOLLTRANS             -311688
#define PD_PTLIDNOTFOUND               -311690
#define PD_PTLALRBLOCKED               -311692
#define PD_PTLALRUNBLOCKED             -311694
#define PD_PTLBLOCKUNBLOCKWRONG        -311696
#define PD_NOTALLOWEDTOBLOCK           -311698
#define PD_PRICELIMITWRONG             -311700
#define PD_SETTLISPASSED               -311702
#define PD_DLVSTARTISPASSED            -311704
#define PD_DLVSTOPISPASSED             -311706
#define PD_FIXINCTYPEWRONG             -311708
#define PD_MODIFIERWRONG               -311710
#define PD_INCEXIST                    -311712
#define PD_INCDIFFER                   -311714
#define PD_COMDIFFER                   -311716
#define PD_UPDHOLDINGNOTALLWD          -311718
#define PD_MODIFIERCHANGED             -311720
#define PD_REFTOPTB                    -311722
#define PD_NOPTB                       -311724
#define PD_NOPTBACT                    -311726
#define PD_PTBONLYINTRADAY             -311728
#define PD_PPRIDTOOLONG                -311730
#define PD_PTLFUTUREDELETE             -311732
#define PD_NOKOSSS                     -311734
#define PD_NOPRM                       -311736
#define PD_NOPRMACT                    -311738
#define PD_PRMIDEMPTY                  -311740
#define PD_REFTOPRM                    -311742
#define PD_ABOVEFOURLEGSNOTALLWD       -311744
#define PD_LEGSNOTINORDER              -311746
#define PD_WRONGPRMETHOD               -311748
#define PD_PRICEMETHODEMPTY            -311750
#define PD_EXPORDELIVEMPTY             -311752
#define PD_MAXCYCLEEXCEED              -311754
#define PD_AVERAGEPRICECBOWRONG        -311756
#define PD_ISINAVAILISTOOLOW           -311758
#define PD_NOMOREISINAVAILABLE         -311760
#define PD_NOISININTERVAL              -311762
#define PD_NOPREVENTMETH               -311764
#define PD_PREVENTMETHEMPTY            -311766
#define PD_CYCLEYEARNOTALLWD           -311768
#define CDB_CGEN_UNDZERO               -314001
#define CDB_CGEN_TOMNYCALL             -314002
#define CDB_CGEN_TOMNYPUT              -314004
#define CDB_CGEN_TOMNYFRWD             -314006
#define CDB_CGEN_COMBCRE                314007
#define CDB_CGEN_COMBEXI                314009
#define CDB_CGEN_NEWUNDER               314011
#define CDB_CGEN_ALTUNDER               314013
#define CDB_CGEN_UNDPRICE               314015
#define CDB_CGEN_NUMCOMB                314017
#define CDB_CGEN_DATEIS                 314019
#define CDB_CGEN_MON                    314021
#define CDB_CGEN_TUE                    314023
#define CDB_CGEN_WED                    314025
#define CDB_CGEN_THU                    314027
#define CDB_CGEN_FRI                    314029
#define CDB_CGEN_SAT                    314031
#define CDB_CGEN_SUN                    314033
#define CDB_SLEC_LOGDEF                 315001
#define CDB_SLEC_NOSTORE                315003
#define CDB_SLEC_STORE                  315005
#define CDB_SLEC_INCNOTFOUND           -315006
#define CDB_SLEC_UPPINSNOTFOUND        -315008
#define CDB_SLEC_INSIDFOUND            -315010
#define CDB_SLEC_ISINFOUND             -315012
#define CDB_SLEC_BINFOUND              -315014
#define CDB_MXLD_ACR_CM_MISS           -320000
#define CDB_MXLD_ACC_INSERT             320001
#define CDB_MXLD_ACC_DELETE             320003
#define CDB_MXLD_COM_DELETE             320005
#define CDB_MXLD_COM_EXISTED            320007
#define CDB_MXLD_COM_INSERT             320009
#define CDB_MXLD_COM_UPDATE             320011
#define CDB_MXLD_INC_DELETE             320013
#define CDB_MXLD_INC_EXISTED            320015
#define CDB_MXLD_INC_INSERT             320017
#define CDB_MXLD_INC_UPDATE             320019
#define CDB_MXLD_INS_DELETE             320021
#define CDB_MXLD_INS_EXISTED            320023
#define CDB_MXLD_INS_INSERT             320025
#define CDB_MXLD_INS_UPDATE             320027
#define CDB_MXLD_SYM_INSERT             320029
#define CDB_MXLD_SYM_DELETE             320031
#define CDB_MXLD_SYM_IGNORED            320033
#define CDB_MXLD_USR_DELETE             320035
#define CDB_MXLD_USR_INSERT             320037
#define CDB_MXLD_USR_UPDATE             320039
#define CDB_MXLD_USR_SUSPEND            320041
#define CDB_MXLD_CST_DELETE             320043
#define CDB_MXLD_CST_INSERT             320045
#define CDB_MXLD_ACRONYMREAD            320047
#define CDB_MXLD_BADGEREAD              320049
#define CDB_MXLD_DELMARK                320051
#define CDB_MXLD_MFIRMREAD              320053
#define CDB_MXLD_OPTSYMREAD             320055
#define CDB_MXLD_OPTSERREAD             320057
#define CDB_MXLD_REGTRADREAD            320059
#define CDB_MXLD_SPECREAD               320061
#define CDB_MXLD_COMPL_OK               320063
#define CDB_SGEN_NON_INT_MODE          -325000
#define CDB_SGEN_ABORT_RTR_WAIT        -325002
#define CDB_SGEN_UNDZERO               -325003
#define CDB_SGEN_TOOMANY_CUR_SER       -325004
#define CDB_SGEN_TOOMANY_CUR_GRP       -325006
#define CDB_SGEN_TOOMANY_SERIES        -325008
#define CDB_SGEN_TOOMANY_STRIKES       -325010
#define CDB_SGEN_ICACHE                -325012
#define CDB_SGEN_IGMT                  -325014
#define CDB_SGEN_IFILL                 -325016
#define CDB_SGEN_IINCR                 -325018
#define CDB_SGEN_IMAX                  -325020
#define CDB_SGEN_SERIES_CREATED         325021
#define CDB_SGEN_SERIES_EXISTED         325023
#define CDB_SGEN_NEWUNDER               325025
#define CDB_SGEN_NEW_INST_CLASS         325027
#define CDB_SGEN_UNDPRICE               325029
#define CDB_SGEN_NUMSERIES              325031
#define CDB_SGEN_DATEIS                 325033
#define CDB_SGEN_NO_NEW_SERIES          325035
#define CDB_SGEN_NOISA                  325037
#define CDB_SGEN_NOISN                  325039
#define CDB_SGEN_IWRONG                 325041
#define CDB_SGEN_IGET                   325043
#define CDB_VPCGWY_OMLOGINGIVEUP       -330000
#define CDB_VPCGWY_MQLOGINGIVEUP       -330002
#define CDB_VPCGWY_NOSYSRES            -330004
#define CDB_VPCGWY_RECOVFILEERR        -330006
#define CDB_VPCGWY_MQDEADMSG           -330008
#define CDB_VPCGWY_ADDFAIL             -330010
#define CDB_VPCGWY_OMQRYFAIL           -330012
#define CDB_VPCGWY_INTERR              -330014
#define CDB_VPCGWY_COMERR              -330016
#define CDB_VPCGWY_OMTRANSERR          -330018
#define CDB_VPCGWY_OMLOGINFAIL         -330019
#define CDB_VPCGWY_OMLOGOUTFAIL        -330021
#define CDB_VPCGWY_MQCONNFAIL          -330023
#define CDB_VPCGWY_MQOPENFAIL          -330025
#define CDB_VPCGWY_MQCLOSEFAIL         -330027
#define CDB_VPCGWY_MQDISCFAIL          -330029
#define CDB_VPCGWY_MQPUTFAIL           -330031
#define CDB_VPCGWY_MQGETFAIL           -330033
#define CDB_VPCGWY_MQTRANSMSG          -330035
#define CDB_VPCGWY_OMLOGINSUC           330037
#define CDB_VPCGWY_OMLOGOUTSUC          330039
#define CDB_VPCGWY_MQCONNSUC            330041
#define CDB_VPCGWY_MQOPENSUC            330043
#define CDB_VPCGWY_MQCLOSESUC           330045
#define CDB_VPCGWY_MQDISCSUC            330047
#define CDB_VPCGWY_MQDQEMPTY            330049
#define CDB_VPCGWY_MQTRANSQEMPTY        330051
#define CDB_VPCGWY_ACTSERIES            330053
#define CDB_VPCGWY_VPCINERR             330055
#define CDB_VPCGWY_OMBRREC              330057
#define CDB_VPCGWY_EXIT                 330059
#define CDB_VPCGWY_START                330061
#define CDB_MDF_VERSION                 335001

/******************************************************************************
*end*of* cdb_messages.h
*******************************************************************************/

#endif /* _CDB_MESSAGES_H_ */


#ifndef _CL_MESSAGES_H_
#define _CL_MESSAGES_H_

/******************************************************************************
Module: cl_messages.h

Message definitions generated 2020-10-21 15:24:28 by amt, version 3.19.7.0 - Built: 2017-12-30.

NOTE: Do not edit this file. It is automatically generated from
      one or more message files.
*******************************************************************************/

#define CL_OK                           700001
#define CL_CMD_QUEUE                    700003
#define CL_COMPLETED                    700005
#define CL_NOQTY                        700007
#define CL_NYI                         -700009
#define CL_INVACCOUNT                  -700011
#define CL_STATEMISMAT                 -700013
#define CL_STATENOTEND                 -700015
#define CL_STATEEND                    -700017
#define CL_PSSTOPUSR                   -700019
#define CL_PSSTOPRSTRT                 -700021
#define CL_PSALRSTOP                   -700023
#define CL_BUFOVFLW                    -700025
#define CL_REQHOLDING                  -700027
#define CL_INVID                       -700028
#define CL_INVMEMBER                   -700030
#define CL_ERRORTBS                    -700032
#define CL_DB_LOCKED                   -700034
#define CL_ILLVERNOUPD                 -700036
#define CL_INVLOGICAL                  -700038
#define CL_NOSERORVAL                  -700040
#define CL_NODEAL                      -700042
#define CL_INVACCORQTY                 -700044
#define CL_INVDEALSOURCE               -700046
#define CL_NODEALPRICE                 -700048
#define CL_INVPOSREQ                   -700050
#define CL_INCBUYSELL                  -700052
#define CL_INVTIME                     -700054
#define CL_INVFIXING                   -700056
#define CL_PRODEVTEXIST                -700058
#define CL_PRODEVTACTIV                -700060
#define CL_FTBNOTFND                   -700062
#define CL_NOFTBORFUNC                 -700064
#define CL_INVOPER                     -700066
#define CL_NOQTYSUPPL                  -700068
#define CL_TRDNOTFND                   -700070
#define CL_TOOMUCHQTY                  -700072
#define CL_NOPOSFND                    -700074
#define CL_TRDNOTSPEC                  -700076
#define CL_TRDSPEC                     -700078
#define CL_EXENOTSUP                   -700080
#define CL_INVEXEREQ                   -700082
#define CL_INVTRANSTYPE                -700084
#define CL_INVTRANSSIZE                -700086
#define CL_PROTOCOLERRE                -700088
#define CL_PROTOCOLERRD                -700090
#define CL_NOITEMS                     -700092
#define CL_TXNOTHANDLED                -700094
#define CL_INTXNDENIED                 -700096
#define CL_INVTRANSRULE                -700098
#define CL_INVTRADESTATE               -700100
#define CL_INCORRECTSUM                -700102
#define CL_INVACCESSW                  -700104
#define CL_INVACCESSR                  -700106
#define CL_INVACCESSE                  -700108
#define CL_POSNOTSUFCLO                -700110
#define CL_INVSTAFORREV                -700112
#define CL_REMNOTQTY                   -700114
#define CL_INVTRDNUM                   -700116
#define CL_TRDNOTTRANS                 -700118
#define CL_INVNBRTRD                   -700120
#define CL_REMTOBIG                    -700122
#define CL_INVTRAIL                    -700124
#define CL_TRANSNOTNEW                 -700126
#define CL_TRANSNOTPLAIN               -700128
#define CL_ADJACCPOS                   -700130
#define CL_INVSERIES                   -700132
#define CL_INVSERORVAL                 -700134
#define CL_INVBASE                     -700136
#define CL_INVULSERIES                 -700138
#define CL_ERRCREACC                   -700140
#define CL_INVACCSTATE                 -700142
#define CL_NOACCCHANGE                 -700144
#define CL_INVACCOUNTE                 -700146
#define CL_INVACCTYP                   -700148
#define CL_INVACCFEETYP                -700150
#define CL_INVCUSTBANK                 -700152
#define CL_INVCOUNTSIGN                -700154
#define CL_ACCISDEFAULT                -700156
#define CL_TRANSANDSINK                -700158
#define CL_INVCHARINACC                -700160
#define CL_ACCOUNT_STATE               -700162
#define CL_ACCOUNT_DUPL                -700164
#define CL_PRODNOTFND                  -700166
#define CL_INVCHGTYP                   -700168
#define CL_INVPSSTATUS                 -700170
#define CL_TMPPRODSTAT                 -700172
#define CL_PRODSTATNOGOOD              -700174
#define CL_LASTSTATE                   -700176
#define CL_FUNCNOTFND                  -700178
#define CL_FUNCTABOVF                  -700180
#define CL_FUNCONLYTRD                 -700182
#define CL_FUNCONLYPOS                 -700184
#define CL_FUNCONLYFLOW                -700186
#define CL_DUPDELITEM                  -700188
#define CL_DELITEMNFND                 -700190
#define CL_PRDDATENFND                 -700192
#define CL_INVWHEN                     -700194
#define CL_FIM_ERROR                   -700196
#define CL_NOPEVRULES                  -700198
#define CL_INVPEVCLASS                 -700200
#define CL_INVXAXISREP                 -700202
#define CL_DECIMLOST                   -700204
#define CL_INVNBRDEC                   -700206
#define CL_PRODNOTSERIES               -700208
#define CL_INVCONTRVAL                 -700210
#define CL_INVCONTRSIZ                 -700212
#define CL_INVSTRIKEPRICE              -700214
#define CL_INVEVTTYPE                  -700216
#define CL_INCPEVDATA                  -700218
#define CL_UNBALDVP                    -700220
#define CL_PANIC                       -700222
#define CL_INVPROGNAME                 -700224
#define CL_INVPROGPARAM                -700226
#define CL_NEWFAILED                   -700228
#define CL_INVLESTATE                  -700230
#define CL_BADEXEQTY                   -700232
#define CL_BADASSIGN                   -700234
#define CL_BADEXEREQ                   -700236
#define CL_NOTRDDEL                    -700238
#define CL_ONLYBINDEALS                -700240
#define CL_TRANSEXIST                  -700242
#define CL_BWNOMATCH                   -700244
#define CL_INVNBRSHARES                -700246
#define CL_INVCOMMODITY                -700248
#define CL_NOSUCHFILE                  -700250
#define CL_ERROPNFIL                   -700252
#define CL_ERRCREFIL                   -700254
#define CL_ERRCLOFIL                   -700256
#define CL_ERRFLUSHFIL                 -700258
#define CL_ERRWRITEFIL                 -700260
#define CL_ERREADFIL                   -700262
#define CL_ENDOFILE                    -700263
#define CL_BUFTOOSMALL                 -700264
#define CL_BADFILFMT                   -700266
#define CL_BADLNKID                    -700268
#define CL_INVALIDLNK                  -700270
#define CL_BADSEQNBR                   -700272
#define CL_DUPLINCACHE                 -700274
#define CL_UNKREPORT                   -700276
#define CL_INVPEVAUTO                  -700278
#define CL_NOIP5DEAL                   -700280
#define CL_INVQTYPARAM                 -700282
#define CL_RTR_ERROR                   -700284
#define CL_INVMASTERPOSCHG             -700286
#define CL_RECOVFAIL                   -700288
#define CL_GDNNOTNEXT                  -700290
#define CL_PRODEVTEXISTSER             -700292
#define CL_NOISSCONVMOD                -700293
#define CL_SRVREJECT                   -700295
#define CL_NOSRVAVAIL                  -700297
#define CL_SERNOTFND                   -700298
#define CL_INVNOMVAL                   -700300
#define CL_INVEXEREQACCTYPE            -700302
#define CL_INVEXEREQACCPROP            -700304
#define CL_UNEXPTRDUPD                 -700306
#define CL_INVAPTQTY                   -700308
#define CL_RRNOTHOLDING                -700310
#define CL_INVEXEREQSTATE              -700312
#define CL_INVEXEREQTYPE               -700314
#define CL_INVPRDEVTREQSTATE           -700316
#define CL_INVEXEREQDATE               -700318
#define CL_INVPRDEVTREQDATE            -700320
#define CL_INVROLLSTATE                -700322
#define CL_INVROLLBACKTYPE             -700324
#define CL_INVROLLBACKPARAMS           -700326
#define CL_SAMEUSER                    -700328
#define CL_INVCANC                     -700330
#define CL_INVREFPRICE                 -700332
#define CL_INVOUTRVAL                  -700334
#define CL_INVSSTNUM                   -700336
#define CL_INVCDCUPD                   -700338
#define CL_DEALNOTSTORED               -700340
#define CL_ROLLNOTENABLED              -700342
#define CL_PROTOCOLERRT                -700344
#define CL_NOTRADEFORAB                -700346
#define CL_NODEALFORAB                 -700348
#define CL_INCONSISTENCYINGIVEUP       -700350
#define CL_KEYTABOFL                   -700352
#define CL_TRDCLDRCHNG                 -700354
#define CL_INVSUBSEVNT                 -700356
#define CL_INVINSTRTYP                 -700358
#define CL_NODUALPOS                   -700360
#define CL_ILLTRNSTIMEINTERVAL         -700362
#define CL_NOTRNSTIMEOBJ               -700364
#define CL_SQLERROR                    -700366
#define CL_NOMATCHOK                   -700368
#define CL_CDCAGTFULL                  -700370
#define CL_NOTHANDLED                   700371
#define CL_NOAGREEMENT                 -700372
#define CL_AUTHBADSEQNBR               -700374
#define CL_AUTHNOENTRY                 -700376
#define CL_AUTHOBJNOTFOUND             -700378
#define CL_TRADESNOTRECOVERED          -700380
#define CL_PEVSERIESEXP                -700382
#define CL_PEVINVREQDATE               -700384
#define CL_FETCHNEXT                   -700386
#define CL_NOTHOLDING                  -700388
#define CL_INVREJECTCONFIRM            -700390
#define CL_OK_ERRLOG                    700391
#define CL_INVALIDPOSOBJ               -700393
#define CL_POSNOTINMAP                 -700395
#define CL_WRONGPOSINMAP               -700397
#define CL_WRONGPSSTATE                -700398
#define CL_TIMEOUT                      700399
#define CL_NOTREALTIME                 -700400
#define CL_OLDPOSINDB                  -700402
#define CL_ILLEXTNONCTDGUP             -700404
#define CL_ILLEXTPASTEXP               -700406
#define CL_ILLEXTTRANSGUP              -700408
#define CL_EXCEPTIONALEVENT             700409
#define CL_INVPOSALGORITHM             -700410
#define CL_INVREQPOSUPD                -700412
#define CL_INVEXEQTY                   -700414
#define CL_RNGERR                      -700415
#define CL_TRDNOGENSTYLEERR            -700416
#define CL_HOLDINGRCTTRD                700417
#define CL_HOLDINGRCTDEAL               700419
#define CL_PENDINGTMDEAL                700421
#define CL_INVFACILITY                 -700422
#define CL_NOCLOGW                     -700424
#define CL_CLHACCNEWCNTRBLANK          -700426
#define CL_NOCLHACCNEWCNTR             -700428
#define CL_FIXINGNOTFOUND              -700430
#define CL_INVCPNLOTS                  -700432
#define CL_ACCTYPENOTCOL               -700434
#define CL_CLEANPRICEDIFF              -700436
#define CL_INVCLEANPRICE               -700437
#define CL_INVDATE                     -700438
#define CL_INVDAYCALCRULE              -700440
#define CL_INCONSPARTY                 -700442
#define CL_NOSYSTEMCLH                 -700444
#define CL_SERINDELIVERY               -700446
#define CL_INVRISKSCALE                -700448
#define CL_INTERNALERROR               -700450
#define CL_PAYMSERMISSING              -700452
#define CL_HOLDINGDEAL                  700453
#define CL_SQLEOS                      -700454
#define CL_NOACCOUNT                   -700455
#define CL_NOTFOUND                     700457
#define CL_BADCONFIG                   -700459
#define CL_INVALIDCONF                 -700461
#define CL_CACHEINVALID                -700463
#define CL_INVPARTCONF                 -700464
#define CL_STALECDCDATA                -700466
#define CL_BADPSSTATE                  -700468
#define CL_DLVFLWNOTFND                -700470
#define CL_SERVERLOST                  -700472
#define CL_CMD_BDX                      700473
#define CL_INVSRVCMD                   -700474
#define CL_UNEXPTXN                    -700476
#define CL_UNEXPBDX                    -700478
#define CL_UNEXPEVENT                  -700480
#define CL_POSSDATALOSS                -700482
#define CL_DUPLICATE                    700483
#define CL_INVCMDCFG                   -700484
#define CL_NODBTXN                     -700486
#define CL_LATECYRCHANGE               -700487
#define CL_INVCOUNTRY                  -700488
#define CL_DUPLPRDSTATE                -700490
#define CL_NOVALIDACKRECVD             -700492
#define CL_DBTXNSTATERR                -700494
#define CL_BADISAPOS                   -700496
#define CL_OMN_FACILITY_BEGIN           704001
#define CL_OMN_NORMAL                   704003
#define CL_OMN_REQHOLDING               704005
#define CL_OMN_BATNTRN                  704007
#define CL_OMN_NOINFO                   704009
#define CL_OMN_BADARGS                 -704010
#define CL_OMN_UKNWNQRY                -704012
#define CL_OMN_SNDFAIL                 -704014
#define CL_OMN_ALRMOV                  -704016
#define CL_OMN_INVBALISS               -704018
#define CL_OMN_INVBALOWN               -704020
#define CL_OMN_INVCOUNTRY              -704022
#define CL_OMN_INVISSOWN               -704024
#define CL_OMN_INVTRANSNUM             -704026
#define CL_OMN_INVVERNO                -704028
#define CL_OMN_RTRERROR                -704030
#define CL_OMN_TXALRSTORED             -704032
#define CL_OMN_BADPOSUPD               -704034
#define CL_OMN_BADSIZE                 -704036
#define CL_OMN_BADSEG                  -704038
#define CL_OMN_BADSEQ                  -704040
#define CL_OMN_ALRCANC                 -704042
#define CL_OMN_DACEMPTY                -704044
#define CL_OMN_INVACCOUNT              -704046
#define CL_OMN_INVBIDASK               -704048
#define CL_OMN_INVDACACC               -704050
#define CL_OMN_INVDEALSRC              -704052
#define CL_OMN_INVINSTRTYP             -704054
#define CL_OMN_INVITMCNT               -704056
#define CL_OMN_INVMARKET               -704058
#define CL_OMN_INVPRICE                -704060
#define CL_OMN_INVQUANT                -704062
#define CL_OMN_INVSERIES               -704064
#define CL_OMN_INVTRANSTYPE            -704066
#define CL_OMN_NODEALFND               -704068
#define CL_OMN_INVTRDID                -704070
#define CL_OMN_INVMEMBER               -704072
#define CL_OMN_INVCHGREQ               -704074
#define CL_OMN_INVACCESSW              -704076
#define CL_OMN_VALIDERR                -704078
#define CL_OMN_STORERR                 -704080
#define CL_OMN_PRODEVTEXIST            -704082
#define CL_OMN_PRODSTATNOGOOD          -704084
#define CL_OMN_INVACCORQTY             -704086
#define CL_OMN_FUNCONLYTRD             -704088
#define CL_OMN_INVACCESSR              -704090
#define CL_OMN_INVACCESSE              -704092
#define CL_OMN_NOQTYSUPPL              -704094
#define CL_OMN_TRDNOTFND               -704096
#define CL_OMN_TOOMUCHQTY              -704098
#define CL_OMN_NOPOSFND                -704100
#define CL_OMN_TRDNOTSPEC              -704102
#define CL_OMN_TRDSPEC                 -704104
#define CL_OMN_EXENOTSUP               -704106
#define CL_OMN_INVEXEREQ               -704108
#define CL_OMN_INVACCOUNTE             -704110
#define CL_OMN_INVACCSTATE             -704112
#define CL_OMN_INVTRADESTATE           -704114
#define CL_OMN_REMTOBIG                -704116
#define CL_OMN_INVID                   -704118
#define CL_OMN_POSNOTSUFCLO            -704120
#define CL_OMN_INCORRECTSUM            -704122
#define CL_OMN_BADXBALVER              -704124
#define CL_OMN_NOXBALVER               -704126
#define CL_OMN_SIGALRREC               -704128
#define CL_OMN_ILLTRNSTIME             -704130
#define CL_OMN_DB_LOCKED               -704132
#define CL_OMN_INVTIME                 -704134
#define CL_OMN_TXNOTHANDLED            -704136
#define CL_OMN_INTXNDENIED             -704138
#define CL_OMN_INVOPER                 -704140
#define CL_OMN_INTERR                  -704142
#define CL_OMN_INVEXCONF               -704144
#define CL_OMN_INVEXREJECT             -704146
#define CL_OMN_INVTRDCONF              -704148
#define CL_OMN_UNKREPORT               -704150
#define CL_OMN_INVMASTERPOSCHG         -704152
#define CL_OMN_INCBUYSELL              -704154
#define CL_OMN_REMNOTQTY               -704156
#define CL_OMN_INVXACCOP               -704158
#define CL_OMN_ABHOLDTRADE             -704160
#define CL_OMN_INVCMTA                 -704161
#define CL_OMN_INVACCTYPE              -704163
#define CL_OMN_INVOPENCLOSE            -704165
#define CL_OMN_CTRSALRPEND             -704166
#define CL_OMN_CRECTRSALRPEND          -704168
#define CL_OMN_DELCTRSALRPEND          -704170
#define CL_OMN_MODCTRSALRPEND          -704172
#define CL_OMN_CTRSFAILED              -704174
#define CL_OMN_NOPENDCTRS              -704175
#define CL_OMN_INVTRADCODE             -704176
#define CL_OMN_ABPENDAFACTRS           -704178
#define CL_OMN_NODEALSTATE             -704180
#define CL_OMN_BADDEALSTATECHANGE      -704182
#define CL_OMN_TMSERNOTDEF             -704184
#define CL_OMN_INVRCTINTRMTRD          -704186
#define CL_OMN_INVRCTINTRMDEAL         -704188
#define CL_OMN_INVRCTAPTDEAL           -704190
#define CL_OMN_NOTANAPTDEAL            -704192
#define CL_OMN_APTRDNOTFND             -704194
#define CL_OMN_INVTRDTYPRCT            -704196
#define CL_OMN_INVACCEDITRA            -704197
#define CL_OMN_INVACCEDITRAN           -704199
#define CL_OMN_INVACCEDIDATD           -704201
#define CL_OMN_INVACCEDIDATE           -704203
#define CL_OMN_TRANSANDSINK            -704204
#define CL_OMN_TRANSNOAUTONET          -704206
#define CL_OMN_NOACCHNGPROP            -704208
#define CL_OMN_NOMODACCDEL             -704210
#define CL_OMN_NOACCHANGEDEL           -704212
#define CL_OMN_INVBNDQUO               -704214
#define CL_OMN_INVPDBNDQUO             -704216
#define CL_OMN_NOPDMATCH               -704218
#define CL_OMN_PHYSNOTREG              -704219
#define CL_OMN_INVDELIVQTY             -704220
#define CL_OMN_INVCSDACC               -704222
#define CL_OMN_TOOFEWITEMS             -704224
#define CL_OMN_BADDCSEQNBR             -704226
#define CL_OMN_INVPOSREQ               -704228
#define CL_OMN_RECDELIV                -704230
#define CL_OMN_TOOMUCHREG              -704232
#define CL_OMN_PDINHOLD                -704234
#define CL_OMN_DELDISTDONE             -704236
#define CL_OMN_INVSTAFORREV            -704238
#define CL_OMN_TRANSNOTNEW             -704240
#define CL_OMN_MEMSUSPCL               -704242
#define CL_OMN_INVTRANSRULE            -704244
#define CL_OMN_INVOUTRVAL              -704246
#define CL_OMN_TOOMANYLEGS             -704248
#define CL_OMN_TRADEMUSTBEACTIVE       -704250
#define CL_OMN_TRADETYPEINVALID        -704252
#define CL_OMN_INVGIVEUPACCESS         -704254
#define CL_OMN_NOTENOUGHREMAINING      -704256
#define CL_OMN_INVGIVEUPACC            -704258
#define CL_OMN_INVGIVEUPACCSTATE       -704260
#define CL_OMN_INVGIVEUPACCTYPE        -704262
#define CL_OMN_GIVEUPNOTHOLDING        -704264
#define CL_OMN_NOTCORRECTSUM           -704266
#define CL_OMN_NOREJECTACCESS          -704268
#define CL_OMN_NOCONFIRMACCESS         -704270
#define CL_OMN_HOLDINGGIVEUP           -704272
#define CL_OMN_HOLDINGRCTTRD           -704274
#define CL_OMN_MARKSTILOP              -704276
#define CL_OMN_INCONSDEALSRC           -704278
#define CL_OMN_INCONSINSTIG            -704280
#define CL_OMN_INCONSTRADETYPE         -704282
#define CL_OMN_INCTRDTYPORDEASRC       -704284
#define CL_OMN_INCONSBUYSELL           -704286
#define CL_OMN_CLSEQNBRTOOLOW          -704288
#define CL_OMN_CLSEQNBRTOOHIGH         -704290
#define CL_OMN_INVTRDDATA              -704292
#define CL_OMN_INVEXTTRDNUM            -704294
#define CL_OMN_GIVEUPNOINST            -704296
#define CL_OMN_RECTNOREV               -704298
#define CL_OMN_ONLYONEDEAL             -704300
#define CL_OMN_INVCLDATE               -704302
#define CL_OMN_INVACCID                -704304
#define CL_OMN_INVCABIND               -704306
#define CL_OMN_INVCLICAT               -704308
#define CL_OMN_INVEXTTRDFEETYP         -704310
#define CL_OMN_INVEXTDEALNUM           -704312
#define CL_OMN_INVQTY                  -704314
#define CL_OMN_TRANSEXIST              -704316
#define CL_OMN_ACCINVALID              -704318
#define CL_OMN_ACCSTATENCHANGE         -704320
#define CL_OMN_RECURSIVEORIG           -704322
#define CL_OMN_INVORIEXTTRDNUM         -704324
#define CL_OMN_INVACCLVL               -704326
#define CL_OMN_INVSUMFLG               -704328
#define CL_OMN_TRANSNOTPLAIN           -704330
#define CL_OMN_EXTRDNBRNOTUNIQUE       -704332
#define CL_OMN_INVWILDSEARCH           -704334
#define CL_OMN_NODEALPRICE             -704336
#define CL_OMN_UNBALQTY                -704338
#define CL_OMN_INVRESIDUAL             -704340
#define CL_OMN_INVINSTIGANT            -704342
#define CL_OMN_INVSTIMEVT              -704344
#define CL_OMN_INVTRADETYPE            -704346
#define CL_OMN_NOTALLACCTYPE           -704348
#define CL_OMN_INVFINALFLG             -704350
#define CL_OMN_INVFIXLABEL             -704352
#define CL_OMN_IDMTMNOTCOMPLETE        -704354
#define CL_OMN_TRADETOOOLD             -704356
#define CL_OMN_CLRDATECLOSED           -704358
#define CL_OMN_CLRDATENOTCLOSED        -704360
#define CL_OMN_CANCNOTALLNONBIN        -704362
#define CL_OMN_CANCNOTALLINST          -704364
#define CL_OMN_CANCNOTALLWUINST        -704366
#define CL_OMN_CANCNOTALLBOX           -704368
#define CL_OMN_CANCTOLATE              -704370
#define CL_OMN_CANCNOTALLNONBIL        -704372
#define CL_OMN_RCTNOTALL               -704374
#define CL_OMN_NOANNULDEAL              704375
#define CL_OMN_CANTNETGUPEXISTS        -704377
#define CL_OMN_COVERCALLNOTPENDING     -704378
#define CL_OMN_INVCOVERCALL            -704380
#define CL_OMN_INVCOVERCALLACCESS      -704382
#define CL_OMN_INVACCOUNTSTATE         -704384
#define CL_OMN_INVACCOUNTSTATEDEL      -704386
#define CL_OMN_NOACCCHANGE             -704388
#define CL_OMN_ACCISDEFAULT            -704390
#define CL_OMN_COVCALLREQDELIV         -704392
#define CL_OMN_COVERCALLISPENDING      -704394
#define CL_OMN_INVGIVUPINTRMTRD        -704396
#define CL_OMN_INVPROPCHAIN            -704398
#define CL_OMN_POSNOTALLOWED           -704400
#define CL_OMN_INVDLVPROP              -704402
#define CL_OMN_INVTRNSTRDTYP           -704404
#define CL_OMN_INVCOVERQTY             -704406
#define CL_OMN_NOMATCHOK               -704408
#define CL_OMN_TRDCABPRICE             -704410
#define CL_OMN_INVPRICEFORMAT          -704412
#define CL_OMN_INVCABPRICEFORMAT       -704414
#define CL_OMN_RCTDSERNOTACTIVE        -704416
#define CL_OMN_INVDENYQTY              -704418
#define CL_OMN_INVTRDITEMNUM           -704420
#define CL_OMN_TRPNOTFOUND             -704422
#define CL_OMN_PARTYTRPNOTFOUND        -704424
#define CL_OMN_INVAUTH                 -704426
#define CL_OMN_ALREADYAUTH             -704428
#define CL_OMN_ILLTRANSUSER            -704430
#define CL_OMN_ILLCOMMODITY            -704432
#define CL_OMN_INVINTMEMBER            -704434
#define CL_OMN_MEMSUSPTRD              -704436
#define CL_OMN_INV2STEPMTMREQ          -704438
#define CL_OMN_INSNOTTRADED            -704440
#define CL_OMN_TRADEDATEPASSED         -704442
#define CL_OMN_INSISSUSP               -704444
#define CL_OMN_NOMATCHSESSION          -704446
#define CL_OMN_INVUSER                 -704448
#define CL_OMN_MEMNOTNOVATE            -704450
#define CL_OMN_INVTIMEVALIDITY         -704452
#define CL_OMN_PARTYNOTNOVATE          -704454
#define CL_OMN_INVNOVINS               -704456
#define CL_OMN_INVSETTLEDATE           -704458
#define CL_OMN_INVOPSETTLE             -704460
#define CL_OMN_MATDATEPASSED           -704462
#define CL_OMN_EXPDATEPASSED           -704464
#define CL_OMN_INVTRTYPE               -704466
#define CL_OMN_INVTRAUTH               -704468
#define CL_OMN_INVTRCAT                -704470
#define CL_OMN_FACEZERO                -704472
#define CL_OMN_FACENEG                 -704474
#define CL_OMN_FACETOBIG               -704476
#define CL_OMN_YIELDNEG                -704478
#define CL_OMN_YIELDTOBIG              -704480
#define CL_OMN_YIELDANDCONSNOTZERO     -704482
#define CL_OMN_INVTICKSIZE             -704484
#define CL_OMN_CONSIDTOBIG             -704486
#define CL_OMN_TRPALRDCANCEL           -704488
#define CL_OMN_SSIALRDCANCEL           -704490
#define CL_OMN_TRPNOVATED              -704492
#define CL_OMN_INVTRPSTATE             -704494
#define CL_OMN_SUBSTATEPENDCANCEL      -704496
#define CL_OMN_ALREADYNOVATED          -704498
#define CL_OMN_ILLNOVREQ               -704500
#define CL_OMN_INVPARTY                -704502
#define CL_OMN_INVTRPSEARCH            -704504
#define CL_OMN_INVBICCODE              -704506
#define CL_OMN_INVNOVATIONPARAM        -704508
#define CL_OMN_INVSSIPARAM             -704510
#define CL_OMN_INVBUYSSIPARAM          -704512
#define CL_OMN_INVSELLSSIPARAM         -704514
#define CL_OMN_INVAGRPARAM             -704516
#define CL_OMN_CHGPCIDNOTALLW          -704518
#define CL_OMN_CHGPCUSNOTALLW          -704520
#define CL_OMN_CHGACIDNOTALLW          -704522
#define CL_OMN_CHGACUSNOTALLW          -704524
#define CL_OMN_CHGACCNOTALLW           -704526
#define CL_OMN_CHGSERNOTALLW           -704528
#define CL_OMN_CHGFVALNOTALLW          -704530
#define CL_OMN_CHGCONSNOTALLW          -704532
#define CL_OMN_CHGYLDNOTALLW           -704534
#define CL_OMN_CHGSETTDTNOTALLW        -704536
#define CL_OMN_CHGTRDDTNOTALLW         -704538
#define CL_OMN_CHGNAMENOTALLW          -704540
#define CL_OMN_CHGBOSNOTALLW           -704542
#define CL_OMN_CHGNOVNOTALLW           -704544
#define CL_OMN_CHGUSESNOTALLW          -704546
#define CL_OMN_CHGUSEANOTALLW          -704548
#define CL_OMN_CHGTRPCNOTALLW          -704550
#define CL_OMN_INVASOF                 -704552
#define CL_OMN_INVCASHACC              -704554
#define CL_OMN_INVSECACC               -704556
#define CL_OMN_INVDVPACC               -704558
#define CL_OMN_INVPARTINFO             -704560
#define CL_OMN_INVNAME                 -704562
#define CL_OMN_YIELDZERO               -704564
#define CL_OMN_INVCONFREJ              -704566
#define CL_OMN_INVSETTLEDOMCUR         -704568
#define CL_OMN_INVOPETRP               -704570
#define CL_OMN_LETTERCONF              -704572
#define CL_OMN_INVBUYCURRENCY          -704574
#define CL_OMN_INVSELLCURRENCY         -704576
#define CL_OMN_INVCURRENCY             -704578
#define CL_OMN_BUYSELLCUREQUAL         -704580
#define CL_OMN_AGRNOTFOUND             -704582
#define CL_OMN_INVAGRTYPE              -704584
#define CL_OMN_INVCANCEL               -704586
#define CL_OMN_INVFORMAT               -704588
#define CL_OMN_AGREEXISTING            -704590
#define CL_OMN_INVFITYPE               -704592
#define CL_OMN_INVCALCRULE             -704594
#define CL_OMN_AMOUNTZERO              -704596
#define CL_OMN_AMOUNTTOBIG             -704598
#define CL_OMN_AMOUNTNEG               -704600
#define CL_OMN_RATENEG                 -704602
#define CL_OMN_RATEZERO                -704604
#define CL_OMN_INVCASHTYPE             -704606
#define CL_OMN_CHGAMNTNOTALLW          -704608
#define CL_OMN_CHGIRATNOTALLW          -704610
#define CL_OMN_SETTLEPASSEDMATDATE     -704612
#define CL_OMN_SETTLEPASSEDEXPDATE     -704614
#define CL_OMN_NOYIELDRTN              -704616
#define CL_OMN_EXRATEZERO              -704618
#define CL_OMN_BUYAMOUNTZERO           -704620
#define CL_OMN_SELLAMOUNTZERO          -704622
#define CL_OMN_INVMETHOD               -704624
#define CL_OMN_CHGBOSAMTNOTALLW        -704626
#define CL_OMN_CHGBOSCURNOTALLW        -704628
#define CL_OMN_CHGBOSSSINOTALLW        -704630
#define CL_OMN_CHGSELLSINOTALLW        -704632
#define CL_OMN_CHGSTLDOMNOTALLW        -704634
#define CL_OMN_CHGMTHDNOTALLW          -704636
#define CL_OMN_SSIEXISTING             -704638
#define CL_OMN_SSINOTFOUND             -704640
#define CL_OMN_INVINSTLEVEL            -704642
#define CL_OMN_MISMATCHINSTLEVEL       -704644
#define CL_OMN_INVNETONTYPE            -704646
#define CL_OMN_NETINPROG               -704648
#define CL_OMN_INVINTPARTY             -704650
#define CL_OMN_CHGAGRTNOTALLW          -704652
#define CL_OMN_CHGINSTTNOTALLW         -704654
#define CL_OMN_AGRALRDCANCEL           -704656
#define CL_OMN_TRPNETTED               -704658
#define CL_OMN_INVNOVYLDCONS           -704660
#define CL_OMN_EXRATENEG               -704662
#define CL_OMN_CHGERATNOTALLW          -704664
#define CL_OMN_DEALPRICENEG            -704666
#define CL_OMN_CONSIDZERO              -704668
#define CL_OMN_CONSIDNEG               -704670
#define CL_OMN_INVTERMDATE             -704672
#define CL_OMN_TERMBEFORESETTLE        -704674
#define CL_OMN_INVRATEINDEX            -704676
#define CL_OMN_INVRATEFIXDATE          -704678
#define CL_OMN_RATEFIXAFTERSETTLE      -704680
#define CL_OMN_INVDAYCOUNT             -704682
#define CL_OMN_CHGDATETERMNOTALLW      -704684
#define CL_OMN_CHGNOTIONALNOTALLW      -704686
#define CL_OMN_CHGFIXRATNOTALLW        -704688
#define CL_OMN_CHGFRIDXNOTALLW         -704690
#define CL_OMN_CHGFIXDATENOTALLW       -704692
#define CL_OMN_CHGDCCONVNOTALLW        -704694
#define CL_OMN_CHGDEALPRICENOTALLW     -704696
#define CL_OMN_CHGQUANTITYNOTALLW      -704698
#define CL_OMN_CHGCURRNOTALLW          -704700
#define CL_OMN_INVFIXING               -704702
#define CL_OMN_DEALPRICEZERO           -704704
#define CL_OMN_CHGCASHRNOTALLW         -704706
#define CL_OMN_CHGUCONSNOTALLW         -704708
#define CL_OMN_CHGUSETTDTNOTALLW       -704710
#define CL_OMN_UCONSIDTOBIG            -704712
#define CL_OMN_CASHRATENEG             -704714
#define CL_OMN_CASHRATETOBIG           -704716
#define CL_OMN_MARGINRATIONEG          -704718
#define CL_OMN_INVUSETTLEDATE          -704720
#define CL_OMN_USETTLEPASSEDMATDATE    -704722
#define CL_OMN_OBJTYPNOTSSI            -704724
#define CL_OMN_OBJTYPNOTAGR            -704726
#define CL_OMN_OPNOTALLMATCHTRP        -704728
#define CL_OMN_FIXSEREXIST             -704730
#define CL_OMN_MISSFIXSERIES           -704732
#define CL_OMN_INVSELLSETTLEINST       -704734
#define CL_OMN_INVBUYSETTLEINST        -704736
#define CL_OMN_SSIBLANK                -704738
#define CL_OMN_FIXEXIST                -704740
#define CL_OMN_INVRATEINDEXPERIOD      -704742
#define CL_OMN_SELLSETTLEINST          -704744
#define CL_OMN_CONSZEROPAYFALSE        -704746
#define CL_OMN_INVPAYSETTLE            -704748
#define CL_OMN_CHGPAYSETTLENOTALLW     -704750
#define CL_OMN_CHGSETTLEFORCURNOTALLW  -704752
#define CL_OMN_INVSETTLEFORCUR         -704754
#define CL_OMN_INVCHARINMSG            -704756
#define CL_OMN_INVRENEGOPER            -704758
#define CL_OMN_INVRENEGTYPE            -704760
#define CL_OMN_NOTOWNERTRP             -704762
#define CL_OMN_INVFRATYPE              -704764
#define CL_OMN_CHGFRATYPENOTALLW       -704766
#define CL_OMN_MARGINRATIOTOBIG        -704768
#define CL_OMN_MEMNOTSWIFT             -704770
#define CL_OMN_PARTYNOTSWIFT           -704772
#define CL_OMN_INVEFFDATE              -704774
#define CL_OMN_EFFNOTSETTLEDATE        -704776
#define CL_OMN_UFACEVALUETOBIG         -704778
#define CL_OMN_INVUFACEVALUE           -704780
#define CL_OMN_INVUCONSIDERATION       -704782
#define CL_OMN_DEDGENMSG               -704784
#define CL_OMN_INVMSGTYPE              -704786
#define CL_OMN_MSGTYPMNYI              -704788
#define CL_OMN_INVRATEFLOAT            -704790
#define CL_OMN_MISSRATEINDEX           -704792
#define CL_OMN_INVRATEINDEXFIXED       -704794
#define CL_OMN_INITRATENEG             -704796
#define CL_OMN_INVROPERIOD             -704798
#define CL_OMN_INVRODAY                -704800
#define CL_OMN_INVFIXEDORFLOAT         -704802
#define CL_OMN_INVUPFPAYER             -704804
#define CL_OMN_NOUPFDATE               -704806
#define CL_OMN_INVUPFDATE              -704808
#define CL_OMN_NOPUPFAMT               -704810
#define CL_OMN_INVUPFAMT               -704812
#define CL_OMN_NOUPFCUR                -704814
#define CL_OMN_INVUPFCUR               -704816
#define CL_OMN_INVCONDITION            -704818
#define CL_OMN_INVCONDCONF             -704820
#define CL_OMN_INVRATERESET            -704822
#define CL_OMN_INVPAYMENTSET           -704824
#define CL_OMN_INVFRD                  -704826
#define CL_OMN_INVIRSWAPTYPE           -704828
#define CL_OMN_INVRENEGCANCEL          -704830
#define CL_OMN_INVRENEGAUTH            -704832
#define CL_OMN_INVRENEGRECTIFY         -704834
#define CL_OMN_INVFLOSTADAT            -704836
#define CL_OMN_BADFLOSTADAT            -704838
#define CL_OMN_INVFLOENDDAT            -704840
#define CL_OMN_BADENDSTODAT            -704842
#define CL_OMN_INVFLOFIXDAT            -704844
#define CL_OMN_BADFLOFIXDAT            -704846
#define CL_OMN_INVFLOSETDAT            -704848
#define CL_OMN_INVFLOPARTY             -704850
#define CL_OMN_INVFLOOP                -704852
#define CL_OMN_INVFLOTYP               -704854
#define CL_OMN_INVFLOTERM              -704856
#define CL_OMN_INVFLODATSEQ            -704858
#define CL_OMN_INVFIRSTSTART           -704860
#define CL_OMN_INVLASTEND              -704862
#define CL_OMN_INVBUSDAYCONV           -704864
#define CL_OMN_INVRESETDAYS            -704866
#define CL_OMN_CHGUPFPAYERNOTALLW      -704868
#define CL_OMN_CHGUPFDATENOTALLW       -704870
#define CL_OMN_CHGUPFAMTNOTALLW        -704872
#define CL_OMN_CHGUPFCURNOTALLW        -704874
#define CL_OMN_CHGBUSDAYCONVNOTALLW    -704876
#define CL_OMN_CHGRATERESETNOTALLW     -704878
#define CL_OMN_CHGRESETDAYSNOTALLW     -704880
#define CL_OMN_CHGPAYMENTSETNOTALLW    -704882
#define CL_OMN_CHGSPREADNOTALLW        -704884
#define CL_OMN_CHGINITIRNOTALLW        -704886
#define CL_OMN_CHGFRODATENOTALLW       -704888
#define CL_OMN_CHGROPERIODNOTALLW      -704890
#define CL_OMN_CHGRODAYNOTALLW         -704892
#define CL_OMN_CHGFIXEDORFLOATNOTALLW  -704894
#define CL_OMN_CHGPARTYPAYNOTALLW      -704896
#define CL_OMN_INVPRINCEXCH            -704898
#define CL_OMN_INVPRINCEXCHDATE        -704900
#define CL_OMN_INVTERMSTATE            -704902
#define CL_OMN_EFFDATELESSSETTLEDATE   -704904
#define CL_OMN_EFFDATELARGERSETTLEDATE -704906
#define CL_OMN_FIRSTTRANSDATE          -704908
#define CL_OMN_SECONDTRANSDATE         -704910
#define CL_OMN_RENEGNOTFOUND           -704912
#define CL_OMN_MEMNOTFULWLD            -704914
#define CL_OMN_AUTHORIZE                704915
#define CL_OMN_AUTHORIZE_UPDATE        -704916
#define CL_OMN_INVFLOWSTATE            -704918
#define CL_OMN_SWAPTERMNOTFOUND        -704920
#define CL_OMN_ALREADYCONF             -704922
#define CL_OMN_INVLEGNUMBER            -704924
#define CL_OMN_INVSWAPTERMOPER         -704926
#define CL_OMN_INVFULLTERM             -704928
#define CL_OMN_INVTERMPAYER            -704930
#define CL_OMN_INVTERMAGREEDATE        -704932
#define CL_OMN_TERMAGREELESSSETTLEDATE -704934
#define CL_OMN_TERMAGREENOTSETTLEDATE  -704936
#define CL_OMN_INVTERMPAYDATE          -704938
#define CL_OMN_TERMPAYLESSSETTLEDATE   -704940
#define CL_OMN_TERMPAYNOTSETTLEDATE    -704942
#define CL_OMN_TERMPAYAMOUNTNEG        -704944
#define CL_OMN_TERMPAYAMOUNTZERO       -704946
#define CL_OMN_INVTERMINFO             -704948
#define CL_OMN_NOTAMOUNTMISSING        -704950
#define CL_OMN_INVNOTAMOUNT            -704952
#define CL_OMN_NOTAMOUNTTOOBIG         -704954
#define CL_OMN_INVSWAPTERMRECTIFY      -704956
#define CL_OMN_INVSWAPTERMCANCEL       -704958
#define CL_OMN_INVSWAPTERMAUTH         -704960
#define CL_OMN_INVSWAPTERMREJECT       -704962
#define CL_OMN_TRPNOTMATCHED           -704964
#define CL_OMN_INVREJECTRENEG          -704966
#define CL_OMN_INVCHGACCUNWIND         -704968
#define CL_OMN_FACEZEROUNWIND          -704970
#define CL_OMN_NOVTRPRENEG             -704972
#define CL_OMN_AUTHINVUSER             -704974
#define CL_OMN_AUTHOBJDIFF             -704976
#define CL_OMN_INVFACEVALUE            -704978
#define CL_OMN_DUPDELFLOWNOTALLW       -704980
#define CL_OMN_DELFLOWNOTFOUND         -704982
#define CL_OMN_MEMPARTYEQUAL           -704984
#define CL_OMN_PERIODSWAPTOOLONG       -704986
#define CL_OMN_PERIODFRATOOLONG        -704988
#define CL_OMN_FLOWAMOUNTZERO          -704990
#define CL_OMN_FLOWAMOUNTTOOBIG        -704992
#define CL_OMN_FLOWAMOUNTNEG           -704994
#define CL_OMN_INVSELLSETTLESSI        -704996
#define CL_OMN_INVSELLSETTLEPAY        -704998
#define CL_OMN_RATEFIXAFTERPAY         -705000
#define CL_OMN_INVMEMFEETYPE           -705002
#define CL_OMN_MEMFEENOTFOUND          -705004
#define CL_OMN_INVMEMFEEOP             -705006
#define CL_OMN_INVMEMFEECHNGACC        -705008
#define CL_OMN_INVMEMFEECHNGEFBD       -705010
#define CL_OMN_INVMEMFEECHNGEF         -705012
#define CL_OMN_INVMEMFEECHNGUPFRONT    -705014
#define CL_OMN_INVFIRSTBILLDATE        -705016
#define CL_OMN_INVENTRFEEBILLDATE      -705018
#define CL_OMN_ENTRFEEZERO             -705020
#define CL_OMN_ENTRFEENEG              -705022
#define CL_OMN_UPFRONTFEEZERO          -705024
#define CL_OMN_UPFRONTFEENEG           -705026
#define CL_OMN_FLOWRATENEG             -705028
#define CL_OMN_FLOWRATEZERO            -705030
#define CL_OMN_FLOWCONSIDNEG           -705032
#define CL_OMN_FLOWCONSIDZERO          -705034
#define CL_OMN_INVCONF                 -705036
#define CL_OMN_QUANTITYZERO            -705038
#define CL_OMN_QUANTITYTOOBIG          -705040
#define CL_OMN_QUANTITYNEG             -705042
#define CL_OMN_INVFROMTERMAGREEDATE    -705044
#define CL_OMN_INVTOTERMAGREEDATE      -705046
#define CL_OMN_FROMAFTERTOTERMDATE     -705048
#define CL_OMN_INVFROMEFFDATE          -705050
#define CL_OMN_INVTOEFFDATE            -705052
#define CL_OMN_FROMAFTERTOEFFDATE      -705054
#define CL_OMN_FLOWCONSIDTOOBIG        -705056
#define CL_OMN_NOTAMOUNTNEG            -705058
#define CL_OMN_TERMPAYAMOUNTTOOBIG     -705060
#define CL_OMN_RECTIFYNOTALLOWED       -705062
#define CL_OMN_INVPARTYACCOUNT         -705064
#define CL_OMN_INVPARTYACCSTATE        -705066
#define CL_OMN_INVPROXYACCOUNT         -705068
#define CL_OMN_INVPROXYACCSTATE        -705070
#define CL_OMN_CASHTRNSFRGRPEXIST      -705072
#define CL_OMN_CHGCASHCODENOTALLW      -705074
#define CL_OMN_CHGPRXYACCNOTALLW       -705076
#define CL_OMN_CHGPARTYACCNOTALLW      -705078
#define CL_OMN_CASHGRPNOTFOUND         -705080
#define CL_OMN_CASHGRPNOTSAME          -705082
#define CL_OMN_FACETOSMALL             -705084
#define CL_OMN_UPFAMOUNTTOOBIG         -705086
#define CL_OMN_CONFNOTNEEDED           -705088
#define CL_OMN_INVTRPSUBSTATE          -705090
#define CL_OMN_INVRATESPREAD           -705092
#define CL_OMN_INVSSISECACC            -705094
#define CL_OMN_INVSSICASHACC           -705096
#define CL_OMN_UNWINDFACEVALPOS        -705098
#define CL_OMN_INVUNWINDCONS           -705100
#define CL_OMN_REPOCNCLFRISTTXDATE     -705102
#define CL_OMN_REPOCNCLSECONDTXDATE    -705104
#define CL_OMN_REPOCNCLUNWIND          -705106
#define CL_OMN_REPOCNCLEXTNOVATED      -705108
#define CL_OMN_YIELDNOTININTRVL        -705110
#define CL_OMN_EXCHGRATENOTININTRVL    -705112
#define CL_OMN_DEALPRICENOTININTRVL    -705114
#define CL_OMN_INTRATENOTININTRVL      -705116
#define CL_OMN_FIXINTRATENOTININTRVL   -705118
#define CL_OMN_CASHRATENOTININTRVL     -705120
#define CL_OMN_INIINTRATENOTININTRVL   -705122
#define CL_OMN_INVEXEREQACCTYPE        -705124
#define CL_OMN_INVTERMSEARCH           -705126
#define CL_OMN_OPERBLANK               -705128
#define CL_OMN_PROBBLANK               -705130
#define CL_OMN_INVEXTTSTATE            -705132
#define CL_OMN_FIXNOTININTRVL          -705134
#define CL_OMN_GIVEUPNOTALLOWED        -705136
#define CL_OMN_INVFEEREBATE            -705138
#define CL_OMN_INVNOVYLD               -705140
#define CL_OMN_NOSWAPFLOW              -705142
#define CL_OMN_INVSPREAD               -705144
#define CL_OMN_INVHOLDDEALTSTATE       -705146
#define CL_OMN_INVORIGHOLDDEAL         -705148
#define CL_OMN_INVNEWHOLDDEAL          -705150
#define CL_OMN_FLWFIXINTRATNOTININTRVL -705152
#define CL_OMN_INVNOVTODAY             -705154
#define CL_OMN_INVNOVFUTURE            -705156
#define CL_OMN_NOVTODAYCLOSED          -705158
#define CL_OMN_NOVFUTURECLOSED         -705160
#define CL_OMN_NOPRINCEXCHDATE         -705162
#define CL_OMN_PRINCEXRATENEG          -705164
#define CL_OMN_PRINCEXRATEZERO         -705166
#define CL_OMN_PRINCEXCHRATENOTININTRV -705168
#define CL_OMN_INVXCURSWAPTYPE         -705170
#define CL_OMN_INVMEMOBJOWN            -705172
#define CL_OMN_INVCHRINKEY             -705174
#define CL_OMN_INVOBJVER               -705176
#define CL_OMN_HOLDINGDEAL             -705178
#define CL_OMN_CHGPRINCEXDATENOTALLW   -705180
#define CL_OMN_CHGPRINCEXRATENOTALLW   -705182
#define CL_OMN_CHGPRINCEXCHNOTALLW     -705184
#define CL_OMN_CHGFIRSTHOLIDAYNOTALLW  -705186
#define CL_OMN_CHGSECONDHOLIDAYNOTALLW -705188
#define CL_OMN_CHGAPPLYHOLIDAYNOTALLW  -705190
#define CL_OMN_CHGCURRENCYNOTALLW      -705192
#define CL_OMN_INVSTATEHOLIDAY         -705194
#define CL_OMN_STATEHOLIDAYEQUAL       -705196
#define CL_OMN_STATEHOLIDAYBLANK       -705198
#define CL_OMN_INVFIRSTTRANSDATE       -705200
#define CL_OMN_INVACCFEEASSOCSAME      -705202
#define CL_OMN_INVACCFEEASSOCOVER      -705204
#define CL_OMN_INVFIXDATECONSID        -705206
#define CL_OMN_INVNOVUNWIND            -705208
#define CL_OMN_FULLTERMALREXIST        -705210
#define CL_OMN_SECNOTAMOUNTMISSING     -705212
#define CL_OMN_INVSECNOTAMOUNT         -705214
#define CL_OMN_SECNOTAMOUNTTOOBIG      -705216
#define CL_OMN_SECNOTAMOUNTNEG         -705218
#define CL_OMN_BADFLOSETDAT            -705220
#define CL_OMN_NONBINARYDEAL           -705222
#define CL_OMN_INVACCALLNOV            -705224
#define CL_OMN_INVEXCRCARCAL           -705226
#define CL_OMN_INVFIRSTCURRENCY        -705228
#define CL_OMN_INVSECCURRENCY          -705230
#define CL_OMN_CURRENCYNOTMATCH        -705232
#define CL_OMN_FEEREBATECCLEVEL        -705234
#define CL_OMN_NOTMATCHPART            -705236
#define CL_OMN_INVTRANSDATENOV         -705238
#define CL_OMN_ACCOUNTNOTNOVATE        -705240
#define CL_OMN_INVTRANSCASHACC         -705242
#define CL_OMN_INVRCTCOMPFLOW          -705244
#define CL_OMN_MATCHSWAPNOTCANC        -705246
#define CL_OMN_NOVTRPNOTCANC           -705248
#define CL_OMN_NETTEDTRPNOTCANC        -705250
#define CL_OMN_NONDOMCURCANCSETTLEDATE -705252
#define CL_OMN_NOOPRCANCREQ            -705254
#define CL_OMN_TRMCLOSED               -705256
#define CL_OMN_TRMCLOSEDTXN            -705258
#define CL_OMN_INVOPAFTERSETTLE        -705260
#define CL_OMN_INVOPAFTEREFFDATE       -705262
#define CL_OMN_INVOPAFTERSECTRANSDATE  -705264
#define CL_OMN_RCTPAYCALCNOTALLW       -705266
#define CL_OMN_RCTFIXINGNOTALLW        -705268
#define CL_OMN_TERMAGREEAFTERTERMDATE  -705270
#define CL_OMN_MATCHAGREEMENTNOTCANC   -705272
#define CL_OMN_ACCTYPNOTTRD            -705274
#define CL_OMN_ACCTYPNOTPOS            -705276
#define CL_OMN_ACCTYPPLAINEW           -705278
#define CL_OMN_ACCTYPBAD               -705280
#define CL_OMN_ONLYOWNERCANCEL         -705282
#define CL_OMN_INVCLHDATECANCEL        -705284
#define CL_OMN_CONREJONLYPARTY         -705286
#define CL_OMN_AUTHDONE                -705288
#define CL_OMN_INSTNOTTRADEDCLICK      -705290
#define CL_OMN_FIRSTTRADETIMENOTPASSED -705292
#define CL_OMN_INVOLDDATE              -705294
#define CL_OMN_INVNEWDATE              -705296
#define CL_OMN_DATENOTMATCHTERM        -705298
#define CL_OMN_INVTYPEOFDATE           -705300
#define CL_OMN_DATENOTMATCHUNWIND      -705302
#define CL_OMN_TERMDATENOTMATCH        -705304
#define CL_OMN_PRINCEXCHDATENOTMATCH   -705306
#define CL_OMN_DATENOTMATCHFLOWSTART   -705308
#define CL_OMN_DATENOTMATCHFLOWEND     -705310
#define CL_OMN_DATENOTMATCHFIXING      -705312
#define CL_OMN_DATENOTMATCHPAYMENT     -705314
#define CL_OMN_DATENOTMATCHPRINCEXCH   -705316
#define CL_OMN_SWAPNOTMATCH            -705318
#define CL_OMN_NOOPRPNDRNG             -705320
#define CL_OMN_NOOPRPNDFXNG            -705322
#define CL_OMN_DEALNOTHOLDING          -705324
#define CL_OMN_DEALNOTFOUND            -705326
#define CL_OMN_TRADEONHOLD             -705328
#define CL_OMN_INVCLHSERIES            -705330
#define CL_OMN_TRADEIDNOTUNIQUE        -705332
#define CL_OMN_EXPDATENOTVALID         -705334
#define CL_OMN_INVEXPDATE              -705336
#define CL_OMN_FPMLSCHEMA              -705338
#define CL_OMN_FPMLFORMAT              -705340
#define CL_OMN_BUSINESSCENTERPRESENT   -705342
#define CL_OMN_BUSINESSCENTERMISSING   -705344
#define CL_OMN_INVDAYTYPECONVENTION    -705346
#define CL_OMN_TRPALRDTERM             -705348
#define CL_OMN_TRPALRDUNWIND           -705350
#define CL_OMN_TRPALRDINCREASE         -705352
#define CL_OMN_FPML_MESSAGEREJECTED     705353
#define CL_OMN_FPML_INVMSGTYPE         -705354
#define CL_OMN_FPML_UNSMSGTYP          -705356
#define CL_OMN_TRADEIDMANDATORY        -705358
#define CL_OMN_INVEXCHLOOKFORINDEX     -705360
#define CL_OMN_INVEXCHTRADEFORSHARE    -705362
#define CL_OMN_INVFUTPRICEFORSHARE     -705364
#define CL_OMN_INVSETTLETYPEFORINDEX   -705366
#define CL_OMN_INVSETTLEPAYFORPHYSETTL -705368
#define CL_OMN_TRADEDATEAFTERPAYDATE   -705370
#define CL_OMN_TRADEDATEAFTERSETTLE    -705372
#define CL_OMN_TRADEDATEAFTEREXPDATE   -705374
#define CL_OMN_COMDATEAFTEREXPDATE     -705376
#define CL_OMN_BUYSELLEQUAL            -705378
#define CL_OMN_STRIKEPRICENEG          -705380
#define CL_OMN_STRIKEPRICEZERO         -705382
#define CL_OMN_NBROFOPTNEG             -705384
#define CL_OMN_NBROFOPTZERO            -705386
#define CL_OMN_NBROFOPTBADFORMAT       -705388
#define CL_OMN_PAYAMOUNTNEG            -705390
#define CL_OMN_PAYAMOUNTZERO           -705392
#define CL_OMN_MINNBROFOPTNEG          -705394
#define CL_OMN_MINNBROFOPTZERO         -705396
#define CL_OMN_MINNBROFOPTBADFORMAT    -705398
#define CL_OMN_INTMULTEXERNEG          -705400
#define CL_OMN_INTMULTEXERZERO         -705402
#define CL_OMN_INTMULTEXERBADFORMAT    -705404
#define CL_OMN_NEWNBROFOPTNEG          -705406
#define CL_OMN_NEWNBROFOPTZERO         -705408
#define CL_OMN_SETTLEAMOUNTNEG         -705410
#define CL_OMN_SETTLEAMOUNTZERO        -705412
#define CL_OMN_NBROFSHARESNEG          -705414
#define CL_OMN_NBROFSHARESZERO         -705416
#define CL_OMN_FORWARDPRICENEG         -705418
#define CL_OMN_FORWARDPRICEZERO        -705420
#define CL_OMN_PRICEPEROPTNEG          -705422
#define CL_OMN_PRICEPEROPTZERO         -705424
#define CL_OMN_NBROFSHARESBADFORMAT    -705426
#define CL_OMN_INVSTRIKEPRICEDEC       -705428
#define CL_OMN_INVPRICEPEROPTDEC       -705430
#define CL_OMN_INVFORWARDPRICEDEC      -705432
#define CL_OMN_TRPTYPENOTEQUAL         -705434
#define CL_OMN_TRPSUBTYPENOTEQUAL      -705436
#define CL_OMN_INVCOMMODITYRIC         -705438
#define CL_OMN_INVCOMMODITYISIN        -705440
#define CL_OMN_COMMODITYDELISTED       -705442
#define CL_OMN_INVPAYMENTDATE          -705444
#define CL_OMN_MSNGFPLMNT              -705446
#define CL_OMN_2MNYFPLMNTS             -705448
#define CL_OMN_BADFPMLSTRCT            -705450
#define CL_OMN_EMPTYFPMLMNT            -705452
#define CL_OMN_NOSTRVAL                -705454
#define CL_OMN_BADFPMLDATEFMT          -705456
#define CL_OMN_XMLMNTNOTFND            -705458
#define CL_OMN_XMLMNTNOTUNIQU          -705460
#define CL_OMN_XMLMNTEXPTD             -705462
#define CL_OMN_XMLMNTNOTI16            -705464
#define CL_OMN_XMLMNTNOTUI16           -705466
#define CL_OMN_XMLMNTNOTUI32           -705468
#define CL_OMN_XMLMNTNOTUI64           -705470
#define CL_OMN_XMLMNTNOTCHAR           -705472
#define CL_OMN_XMLMNTNOTDATE           -705474
#define CL_OMN_XMLNOATTRIB             -705476
#define CL_OMN_XMLATTRIBNOTFND         -705478
#define CL_OMN_FPMLNOTNUMERIC          -705480
#define CL_OMN_UNEXPFPMLMNT            -705482
#define CL_OMN_INVXMLREF               -705484
#define CL_OMN_FPMLNOTSUPP             -705486
#define CL_OMN_MAXSWAPFLOWS            -705488
#define CL_OMN_INVOPAFTERTERMDATE      -705490
#define CL_OMN_INVRENEGREJECT          -705492
#define CL_OMN_INVRECTIFYRENEG         -705494
#define CL_OMN_INVCANCELRENEG          -705496
#define CL_OMN_MARGINRATIONOTININTRVL  -705498
#define CL_OMN_CHGMARGINRATIONOTALLW   -705500
#define CL_OMN_CASHTRNSFRGRPROWEXIST   -705502
#define CL_OMN_REPOCNCLFULLUNWOUND     -705504
#define CL_OMN_INVCALCUNWINDCONSID     -705506
#define CL_OMN_NOTOWNERAGREEMENT       -705508
#define CL_OMN_NOTOWNERTERMINATION     -705510
#define CL_OMN_NOTOWNERUNWIND          -705512
#define CL_OMN_NOTOWNERRENEG           -705514
#define CL_OMN_RENEGNOTALLWUNWIND      -705516
#define CL_OMN_MEMNOTAUTHONBEHALF      -705518
#define CL_OMN_MEMPARTYEQUALAGR        -705520
#define CL_OMN_NODBLVALU               -705522
#define CL_OMN_NOINTVALU               -705524
#define CL_OMN_NOUINTVALU              -705526
#define CL_OMN_BADSCHEMALOC            -705528
#define CL_OMN_UNKNOWNBIC              -705530
#define CL_OMN_BADFPMLMNTVALUE         -705532
#define CL_OMN_INVOPTYPE               -705534
#define CL_OMN_INVOPTSTYLE             -705536
#define CL_OMN_INVSETTLTYPE            -705538
#define CL_OMN_ISINOTFND               -705540
#define CL_OMN_TMRKTNOTFND             -705542
#define CL_OMN_INSTYPNOTFND            -705544
#define CL_OMN_TMPLSERNOTFND           -705546
#define CL_OMN_PRICEPEROPTTOOBIG       -705548
#define CL_OMN_STRIKEPRICETOOBIG       -705550
#define CL_OMN_FORWARDPRICETOOBIG      -705552
#define CL_OMN_NOPTID                  -705554
#define CL_OMN_MISNGPTID               -705556
#define CL_OMN_2MNYPTID                -705558
#define CL_OMN_CANTCMP                 -705560
#define CL_OMN_DIFFPRD                 -705562
#define CL_OMN_NOFPMLPROD              -705564
#define CL_OMN_NOFPMLPRODCB            -705566
#define CL_OMN_2MNYSGMNTS              -705568
#define CL_OMN_OPNINTSIGRCVD           -705570
#define CL_OMN_INVSETTLETYPEPRODUCT    -705572
#define CL_OMN_USANDEUNOTCOMP          -705574
#define CL_OMN_STANDALONENOTEQUAL      -705576
#define CL_OMN_CHANGEFORMATNOTALLW     -705578
#define CL_OMN_INVMULTEXCHFORSHARE     -705580
#define CL_OMN_ONLY_CLOSING            -705581
#define CL_OMN_INVCOMMODITYCUR         -705582
#define CL_OMN_INVPARTSERIES           -705584
#define CL_OMN_NOCANCELPRICECORR       -705586
#define CL_OMN_TXNONCLASSDENIED        -705588
#define CL_OMN_UNDEFACP                -705590
#define CL_OMN_TRDREPNOTINIT           -705592
#define CL_OMN_TRDREPNOTFND            -705594
#define CL_OMN_INVINSTANCENUMBER       -705596
#define CL_OMN_INVDEALCOLSEQUENCE      -705598
#define CL_OMN_CANOLDNOTALLW           -705600
#define CL_OMN_INVCANTRDID             -705602
#define CL_OMN_DATAINCOMPLETE          -705604
#define CL_OMN_DATAPURGED               705605
#define CL_OMN_INVSERTRDSLP            -705606
#define CL_OMN_CANITNNOTALLW           -705608
#define CL_OMN_DATAINCOMPLETE_NORECOV  -705610
#define CL_OMN_EXTIDBLANK              -705612
#define CL_OMN_EXTIDEXIST              -705614
#define CL_OMN_BADASOF                 -705616
#define CL_OMN_EXTIDNOTFND             -705618
#define CL_OMN_OBLRIGHTNOTFND          -705620
#define CL_OMN_INVCONTROLLER           -705622
#define CL_OMN_INVREGISTRAR            -705624
#define CL_OMN_DUPACCREGCONTROL        -705626
#define CL_OMN_NOTSECLEND              -705628
#define CL_OMN_NOTPOOLTYPE             -705630
#define CL_OMN_NOTBILTYPE              -705632
#define CL_OMN_EFFPASSEDLASTTRDDATE    -705634
#define CL_OMN_USETTLEPASSEDLASTTRD    -705636
#define CL_OMN_INVFROMSETTDATE         -705638
#define CL_OMN_INVTOSETTDATE           -705640
#define CL_OMN_FROMAFTERTOSETTDATE     -705642
#define CL_OMN_WILDCARDNOTALLOWED      -705644
#define CL_OMN_INVPOSADJAMT            -705645
#define CL_OMN_OLDTRDNOTALWAPT         -705646
#define CL_OMN_INVQTYINCR              -705648
#define CL_OMN_ACCALIASNOTUNIQUE       -705650
#define CL_OMN_INVCHARINACCALIAS       -705652
#define CL_OMN_CANCLOLDAPTNOTALLWD     -705654
#define CL_OMN_POSNOTFND               -705656
#define CL_OMN_INVEXTACCRTYPE          -705658
#define CL_OMN_INVEXTACCCONTR          -705660
#define CL_OMN_INVEXTACCVER            -705662
#define CL_OMN_EXTACCCONEXISTS         -705664
#define CL_OMN_NOEXTACCCON             -705666
#define CL_OMN_UPDEXTACCNOTALLW        -705668
#define CL_OMN_INVTRDSESSTATE          -705670
#define CL_OMN_GUPNEWCONTRNOTALLWD      705671
#define CL_OMN_RCTACCNEWCONTRNOTALLWD   705673
#define CL_OMN_RCTNEWCONTRNOTALLWD      705675
#define CL_OMN_INVDAYSRESTRID          -705676
#define CL_OMN_INVCLOSEOUTQTY          -705678
#define CL_OMN_REINSTATENOTFND         -705680
#define CL_OMN_REINSTATENOTALLWD       -705682
#define CL_OMN_INVACCEDIPOS            -705684
#define CL_OMN_NOMODACCTYPORIGIN       -705686
#define CL_OMN_NOMODACCTYP             -705688
#define CL_OMN_INVCONSTCLOFIHELDQTY    -705690
#define CL_OMN_FINHELDADJNOTALLWD      -705692
#define CL_OMN_NEGCLOSEOUT             -705694
#define CL_OMN_NEGFINHELD              -705696
#define CL_OMN_NEGREINSTATEQTY         -705698
#define CL_OMN_CLOSEOUTNOTALLWD        -705700
#define CL_OMN_CLOSEOUTFUTNOTALLWD     -705702
#define CL_OMN_REINSTATEFUTNOTALLWD    -705704
#define CL_OMN_INVREINSTATEQTY         -705706
#define CL_OMN_EXCLREQEXISTS           -705708
#define CL_OMN_REINCLREQEXISTS         -705710
#define CL_OMN_DEALTOOLDEXCL           -705712
#define CL_OMN_INVEXCLREQUEST          -705714
#define CL_OMN_QRYDATEINV              -705716
#define CL_OMN_DEALRECTEXCL            -705718
#define CL_OMN_ONLYALLOWRCTPRICECBO    -705720
#define CL_OMN_FINALHELDTOOBIG         -705722
#define CL_OMN_NOPOSADJ                 705723
#define CL_OMN_INVREQDATE              -705724
#define CL_OMN_INVACCTYPFORSTATECHNG   -705726
#define CL_OMN_RCTCOMBONOTALLWD         705727
#define CL_OMN_NOFASTPURSYM            -705729
#define CL_OMN_NOFASTPURSYMDAYS        -705730
#define CL_OMN_TRPCODENOTFND           -705732
#define CL_OMN_INCONSOCR               -705734
#define CL_OMN_ACTIVEACCDEP            -705735
#define CL_OMN_NONLCLTRNSGUP           -705736
#define CL_OMN_ILLDSTMEMINS            -705738
#define CL_OMN_POSTRANSNOTALL          -705740
#define CL_OMN_DUPLPOSCLOSEOUT         -705742
#define CL_OMN_NOITEMS                 -705744
#define CL_OMN_CBOGUPNOTALL            -705746
#define CL_OMN_GUPSERNOTACT            -705748
#define CL_OMN_WRONGUPSER              -705750
#define CL_OMN_REQNOTPENDING           -705752
#define CL_OMN_INVLESTATE              -705754
#define CL_OMN_CTDPOSNOTSET            -705756
#define CL_OMN_NOSTNDALONGUP           -705758
#define CL_OMN_TXNTOOLATE              -705760
#define CL_OMN_DIFFERENTCLEARINGORG    -705762
#define CL_OMN_INVMEMINACC             -705764
#define CL_OMN_INVSETTLECLASS          -705766
#define CL_OMN_INVEXTACCRSTATE         -705768
#define CL_OMN_INVEXTACCID             -705770
#define CL_OMN_FEEASSOCACCANDTYPE      -705772
#define CL_OMN_INVMARGINCLASS          -705773
#define CL_OMN_IFACIDXNOTPOSSIBLE      -705774
#define CL_OMN_IFACREFNOTPOSSIBLE      -705776
#define CL_OMN_INVRISKCURCONV          -705778
#define CL_OMN_INVRISKMARGINNET        -705780
#define CL_OMN_INVEXTACCINTERM         -705782
#define CL_OMN_NOACCCHANGEINACTIVE     -705784
#define CL_OMN_NOINTEGRITYDEF          -705785
#define CL_OMN_INVAMOUNT               -705786
#define CL_OMN_INVTERMPAYAMOUNT        -705788
#define CL_OMN_INVFLOWAMOUNT           -705790
#define CL_OMN_INVCONSIDERATION        -705792
#define CL_OMN_INVFIRSTSTUB            -705794
#define CL_OMN_INVLASTSTUB             -705796
#define CL_OMN_INVRCFACCMATCHED        -705798
#define CL_OMN_INVCONFUSER             -705800
#define CL_OMN_NOTPENDINGCLMEMACC      -705802
#define CL_OMN_INVTRDANDPOSACCCLH      -705804
#define CL_OMN_INVPOSACCANDCONFMEM     -705806
#define CL_OMN_INVPDNCLHCONF           -705808
#define CL_OMN_INVCOLLHAND             -705810
#define CL_OMN_INVUPFRONT              -705812
#define CL_OMN_EXPNOTINFUTURE          -705814
#define CL_OMN_EXPBEFOREEFF            -705816
#define CL_OMN_FRAINTRATNOTININTRVL    -705818
#define CL_OMN_ACCPROPDELIVERY         -705820
#define CL_OMN_ACCPROPSETTLEMENT       -705822
#define CL_OMN_NOABSTARTSESS           -705824
#define CL_OMN_INIINTRATEMISSING       -705826
#define CL_OMN_INVSETTLINSTR           -705828
#define CL_OMN_INVLEGALACCINSTR        -705830
#define CL_OMN_COLLCHECK                705831
#define CL_OMN_PRENOVREQ               -705833
#define CL_OMN_PRENOVREQFAIL           -705834
#define CL_OMN_INVEXPLIMIT             -705836
#define CL_OMN_NOABSTARTEOD            -705838
#define CL_OMN_OLDGUPTRANSITORY        -705840
#define CL_OMN_INVRCTADJTRD            -705842
#define CL_OMN_ISSUEPENDING            -705844
#define CL_OMN_NOANULPARTXFR           -705846
#define CL_OMN_RCTRDBEFRGUP            -705848
#define CL_OMN_INVMIXCLDATE            -705850
#define CL_OMN_FUTEXPNOTSUPP           -705852
#define CL_OMN_LARGEDATA               -705853
#define CL_OMN_ONLYCANCLALLWD          -705855
#define CL_OMN_RCTRDREQEXIST           -705856
#define CL_OMN_RCTDEALREQEXIST         -705858
#define CL_OMN_INVALLOWTAKEUP          -705860
#define CL_OMN_INVAUTOTAKEUP           -705862
#define CL_OMN_AATINVALIDCONNECTION    -705864
#define CL_OMN_AATCONNECTIONEXIST      -705866
#define CL_OMN_TAKEUPNOLIMIT           -705868
#define CL_OMN_INVGROSSNET             -705870
#define CL_OMN_INVSETPRODFORMAT        -705872
#define CL_OMN_SETPRODEXIST            -705874
#define CL_OMN_CCNOTALLOW              -705876
#define CL_OMN_NETMUSTEXIST            -705878
#define CL_OMN_MEMUSECMACC             -705880
#define CL_OMN_AATCNXNOTFOUND          -705882
#define CL_OMN_AATNOTFOUND             -705884
#define CL_OMN_MANYPARTTACNX           -705886
#define CL_OMN_ONLYCMCNX               -705888
#define CL_OMN_INVAATC                 -705890
#define CL_OMN_INVAAT                  -705892
#define CL_OMN_NODELCNXAATC            -705894
#define CL_OMN_ILLVERNOUPD             -705896
#define CL_OMN_INVALLOWALLACCOUNT      -705898
#define CL_OMN_BADREINSTATEQTY         -705900
#define CL_OMN_INVPARTAATCNX           -705902
#define CL_OMN_FOREIGNACCS             -705904
#define CL_OMN_INVAATCNXTYPE           -705906
#define CL_OMN_AATCNXEXISTS            -705908
#define CL_OMN_AATNOTACTIVE            -705910
#define CL_OMN_ACCINRGALRDY            -705912
#define CL_OMN_ALLACCAATNOTALLWD       -705914
#define CL_OMN_INVIMSTRUCT             -705916
#define CL_OMN_MODAATRGCNXNOTSUP       -705918
#define CL_OMN_ACCANDALLACCINV         -705920
#define CL_OMN_ACCNOTINRGMAP           -705922
#define CL_OMN_ACCDUPLINAAT            -705924
#define CL_OMN_ACCORIGININCONS         -705926
#define CL_OMN_INCOMPATRDACCONF        -705928
#define CL_OMN_INCOMPATRDACCFND        -705930
#define CL_OMN_BADIDFORMAT             -705932
#define CL_OMN_INVCCYRANK              -705934
#define CL_OMN_INVCCLAMOUNT            -705936
#define CL_OMN_INVDCLAMOUNT            -705938
#define CL_OMN_INVCCCCYSER             -705940
#define CL_OMN_INVVERNOUPD             -705942
#define CL_OMN_INVCYRCNX               -705944
#define CL_OMN_DUPCCCCYSER             -705946
#define CL_OMN_ILLCHGCCLAMT            -705948
#define CL_OMN_DELCCYNOTALLWD          -705950
#define CL_OMN_DUPLACC                 -705952
#define CL_OMN_INVDDBASECCY            -705954
#define CL_OMN_CCYRNKINUSE             -705956
#define CL_OMN_ILLCHGDCLAMT            -705958
#define CL_OMN_INVEXCLFCST             -705960
#define CL_OMN_DB_NODATAFOUND          -705962
#define CL_OMN_AATINVACCSTATE          -705964
#define CL_OMN_AATINVACCMEM            -705966
#define CL_OMN_AATINVACCOUNT           -705968
#define CL_OMN_AATINVACCWILD           -705970
#define CL_OMN_CLOSEOUTPROBLEM         -705971
#define CL_OMN_ORIGAFAOUTDATED         -705972
#define CL_OMN_NEWAFAOUTDATED          -705974
#define CL_OMN_ORIGAFAINUSE            -705976
#define CL_OMN_NEWAFAVLDTOOSOON        -705978
#define CL_OMN_TOOMANYAATACCS          -705980
#define CL_OMN_NOMOREDATA              -705981
#define CL_OMN_FACILITY_END             705983
#define CL_OCC_CHGCLOSETOOPENBUY       -708001
#define CL_OCC_CHGCLOSETOOPENSELL      -708003
#define CL_OCC_CHGCLOSETOOPENBOTH      -708005
#define CL_OCC_NONNUMTRADEDATE         -708007
#define CL_OCC_TRADEDATENOTCUR         -708009
#define CL_OCC_NONNUMTRDEXTIME         -708011
#define CL_OCC_NONNUMTRDNUMBER         -708013
#define CL_OCC_NONNUMTRDPRICE          -708015
#define CL_OCC_NONNUMTRDVOL            -708017
#define CL_OCC_INVCHGCODE              -708019
#define CL_OCC_INVBUYMEM               -708021
#define CL_OCC_INVBUYACC               -708023
#define CL_OCC_INVBUYOPCL              -708025
#define CL_OCC_INVSELLMEM              -708027
#define CL_OCC_INVSELLACC              -708029
#define CL_OCC_INVSELLOPCL             -708031
#define CL_OCC_INVCHGSELLOPCL          -708033
#define CL_OCC_INVBUYOCCHGTR           -708035
#define CL_OCC_INVSELLOCCHGTR          -708037
#define CL_OCC_INVCHGBUYOPCL           -708039
#define CL_OCC_INVSERIES               -708041
#define CL_OCC_CLTRDBUYACC             -708043
#define CL_OCC_CLTRDSELLAC             -708045
#define CL_OCC_SELLINSUFPOS            -708047
#define CL_OCC_BUYINSUFPOS             -708049
#define CL_OCC_INVMEMBER               -708051
#define CL_OCC_INVACCOUNT              -708053
#define CL_OCC_EXERCVOLZERO            -708055
#define CL_OCC_INVEXERCVOL             -708057
#define CL_OCC_UNCLTRDCHG              -708059
#define CL_OCC_ALRTRDCHG               -708061
#define CL_OCC_PREMEXBYEX              -708063
#define CL_OCC_DUPLTRDNUMBER           -708065
#define CL_OCC_BUYGUPFORHOUSE          -708067
#define CL_OCC_SELLGUPFORHOUSE         -708069
#define CL_OCC_BUYGUPCHGREQ            -708071
#define CL_OCC_BUYGUPDELREQ            -708073
#define CL_OCC_SELLGUPCHGREQ           -708075
#define CL_OCC_SELLGUPDELREQ           -708077
#define CL_OCC_INVBUYGUPREQTR          -708079
#define CL_OCC_INVSELLGUPREQTR         -708081
#define CL_OCC_INVBUYGUP               -708083
#define CL_OCC_INVSELLGUP              -708085
#define CL_OCC_INVBUYSELLGUP           -708087
#define CL_OCC_INVBUYGUPBUYCHG         -708089
#define CL_OCC_INVBUYGUPSELLCHG        -708091
#define CL_OCC_INVBUYGUPBUYSELLCHG     -708093
#define CL_OCC_INVSELLGUPBUYCHG        -708095
#define CL_OCC_INVSELLGUPSELLCHG       -708097
#define CL_OCC_INVSELLGUPBUYSELLCHG    -708099
#define CL_OCC_INVBUYSELLGUPBUYCHG     -708101
#define CL_OCC_INVBUYSELLGUPSELLCHG    -708103
#define CL_OCC_INVBUYSELLGUPBUYSELLCHG -708105
#define CL_DC_TRDCHANGED               -709001
#define CL_DC_TRDREJECT                -709003
#define CL_MDF_VERSION                  710001

/******************************************************************************
*end*of* cl_messages.h
*******************************************************************************/

#endif /* _CL_MESSAGES_H_ */


#ifndef _CM_MESSAGES_H_
#define _CM_MESSAGES_H_

/******************************************************************************
Module: cm_messages.h

Message definitions generated 2020-10-21 15:24:28 by amt, version 3.19.7.0 - Built: 2017-12-30.

NOTE: Do not edit this file. It is automatically generated from
      one or more message files.
*******************************************************************************/

#define CM_OK                           1800001
#define CM_CMD_QUEUE                    1800003
#define CM_COMPLETED                    1800005
#define CM_INVSERIES                   -1800006
#define CM_INVMEMBER                   -1800008
#define CM_INVINTMEMBER                -1800010
#define CM_COLNOTFOUND                 -1800012
#define CM_INVTRANSSIZE                -1800014
#define CM_CHGPCUSNOTALLW              -1800016
#define CM_CHGACIDNOTALLW              -1800018
#define CM_CHGSERNOTALLW               -1800020
#define CM_CHGTRDDTNOTALLW             -1800022
#define CM_CHGACUSNOTALLW              -1800024
#define CM_PANIC                       -1800026
#define CM_DB_LOCKED                   -1800028
#define CM_ILLTRANSUSER                -1800030
#define CM_MEMSUSPCL                   -1800032
#define CM_INSNOTTRADED                -1800034
#define CM_TRADEDATEPASSED             -1800036
#define CM_INTXNDENIED                 -1800038
#define CM_ILLCOMMODITY                -1800040
#define CM_ILLTRNSTIME                 -1800042
#define CM_INVCOLTYPE                  -1800044
#define CM_MATDATEPASSED               -1800046
#define CM_EXPDATEPASSED               -1800048
#define CM_INVTIME                     -1800050
#define CM_INVASOF                     -1800052
#define CM_INVNAME                     -1800054
#define CM_INVACCSTATE                 -1800056
#define CM_INVACCOUNT                  -1800057
#define CM_NOTALLACCTYPE               -1800058
#define CM_INVGUARANTEETYPE            -1800060
#define CM_INVMEMBERDEPTYPE            -1800062
#define CM_INVUSER                     -1800064
#define CM_INSISSUSP                   -1800066
#define CM_INVCURRENCY                 -1800068
#define CM_INVMARGINCLASS              -1800070
#define CM_INVMARGINDATE               -1800072
#define CM_MARGINREQNEG                -1800074
#define CM_INVSETTLECLASS              -1800076
#define CM_INVSETTLEDATE               -1800078
#define CM_SETTLEREQNEG                -1800080
#define CM_INVPOSDATE                  -1800082
#define CM_MARACCNOTFOUND              -1800084
#define CM_FIXNOTFOUND                 -1800086
#define CM_COLACCNOTFOUND              -1800088
#define CM_FUNCNOTFND                  -1800090
#define CM_RISKCURNOTFOUND             -1800092
#define CM_SETTCURNOTFOUND             -1800094
#define CM_INVVALUATIONDATE            -1800096
#define CM_INVISINTRADAY               -1800098
#define CM_INVCOLCHTYPE                -1800100
#define CM_BADSEG                      -1800102
#define CM_BADSEQ                      -1800104
#define CM_COLALRDCANCEL               -1800106
#define CM_COLNOTACTIVE                -1800108
#define CM_NOCOLLRTN                   -1800110
#define CM_COLSTATENOTFOUND            -1800112
#define CM_NOTSUSPENDED                -1800114
#define CM_NOTPENDORPROC               -1800116
#define CM_BANKINSTNOTFOUND            -1800118
#define CM_INVSTATE                    -1800120
#define CM_ACCTYPENOTCOL               -1800122
#define CM_INSTNOTCOL                  -1800124
#define CM_MEMBERDEPNOTNEG             -1800126
#define CM_MEMBERDEPEXISTING           -1800128
#define CM_INVBANKACC                  -1800130
#define CM_INVBANKACC2                 -1800132
#define CM_NOBANKINSTCRE               -1800133
#define CM_MISSINGBANKACC              -1800134
#define CM_MISSINGBANK                 -1800136
#define CM_INVCREATEBANK               -1800138
#define CM_EFFECTIVEDATEPASSED         -1800140
#define CM_INVEFFECTIVEDATE            -1800142
#define CM_ACCTYPENOTMEMDEP            -1800144
#define CM_CASHCOLLEXISTING            -1800146
#define CM_EXRATENOTFOUND              -1800148
#define CM_EXRATEFIXNOTFOUND           -1800150
#define CM_CASHCOLNEG                  -1800152
#define CM_INVSTATECHANGE              -1800154
#define CM_AMOUNTNEG                   -1800156
#define CM_AMOUNTPOS                   -1800158
#define CM_AMOUNTTOOBIG                -1800160
#define CM_CHGMEMDEPNOTALLW            -1800162
#define CM_RCTBNKONLYFAILED            -1800164
#define CM_RSNDBNKONLYFAILED           -1800166
#define CM_BANKACCBLANK                -1800168
#define CM_BICBLANK                    -1800170
#define CM_NAMEBLANK                   -1800172
#define CM_TRANSFERIDBLANK             -1800174
#define CM_INVSENDER                   -1800176
#define CM_REQUESTNBRZERO              -1800178
#define CM_BANKINSTEXISTS              -1800180
#define CM_INVSECURITYTYPE             -1800182
#define CM_EXRATERIVANOTFOUND          -1800184
#define CM_INVEFFECTIVEUNTIL           -1800186
#define CM_EFFECTIVEUNTILPASSED        -1800188
#define CM_EFFUNTILLESSEFFDATE         -1800190
#define CM_COLEXPIRED                  -1800192
#define CM_NOCALCRTN                   -1800194
#define CM_REQUESTNBRNOTZERO           -1800196
#define CM_DUPUPDATEINTXN2050          -1800198
#define CM_DUPUPDATEINTXN2049          -1800200
#define CM_INVCOLLINFOINSTTYPE         -1800202
#define CM_INVISFINAL                  -1800204
#define CM_INVISEXTERNAL               -1800206
#define CM_INVPAYMENTCHTYPE            -1800208
#define CM_PAYMENTINSTNOTFOUND         -1800210
#define CM_SECURITYEXISTING            -1800212
#define CM_NOTEXTERNALEVAL             -1800214
#define CM_DUPUPDATEINTXN              -1800216
#define CM_INVCMSEXCHANGE              -1800218
#define CM_INVEXTACCREGISTRAR          -1800220
#define CM_SEGMENTNBROUTOFSEQ          -1800222
#define CM_INVSWIFTTYPE                -1800224
#define CM_SETTLEMENTNOTREADY          -1800226
#define CM_INVFACILITY                 -1800228
#define CM_INVPISTATECHANGE            -1800230
#define CM_PAYMENTINSTALRDYMARKED      -1800232
#define CM_PAYINSTNBRZERO              -1800234
#define CM_PAYINSTNOTINSENTREJECT      -1800236
#define CM_PAYINSTNOTINMANUAL          -1800238
#define CM_NOSETTLEMENTAVAILABLE       -1800240
#define CM_PAYMENTSNOTCOMPLETED        -1800242
#define CM_PAYMENTINSTALRDYREJECTED    -1800244
#define CM_EARLIERPAYINCOMPEXISTS      -1800246
#define CM_LATERPAYINCOMPEXISTS        -1800248
#define CM_ALLPAYEMENTSZERO            -1800250
#define CM_NORAZORGWY                  -1800252
#define CM_NOSETTLEMENTHANDLED         -1800254
#define CM_WAITINGEODPAYMENTS          -1800255
#define CM_MANUALREJECTNOTALLOWED      -1800256
#define CM_INVFIXINGHOLDERSERIES       -1800258
#define CM_INVPREMIUMUNIT              -1800260
#define CM_DBDUPLICATE                  1800261
#define CM_INVACCINTQUERYTYPE          -1800262
#define CM_GENCOLLNBRFAILED            -1800264
#define CM_DBTXNOTSTARTED              -1800266
#define CM_WAITINGCOLLSTATE            -1800267
#define CM_PAYMENTSTATENOTFOUND        -1800268
#define CM_COLLATERALSTATENOTFOUND     -1800270
#define CM_NOPAYEMENTS                 -1800272
#define CM_GUARANTEEEXISTING           -1800274
#define CM_MARGINEODNOTREADY           -1800276
#define CM_INVCLHID                    -1800278
#define CM_PAYMENTINSTSENTREJECT        1800279
#define CM_SEREJECTEDPAYMARK           -1800280
#define CM_REQQRYNOTGRANTED            -1800282
#define CM_SEREJECTEDADDINST           -1800284
#define CM_NOCOLTIMERFOUND             -1800285
#define CM_NOVALGROUPFOUND             -1800287
#define CM_INVSSTNUM                   -1800288
#define CM_NOMATCHSESSION              -1800290
#define CM_INVCOLTRANTYPE              -1800292
#define CM_INSTREFNOTUNIQ              -1800294
#define CM_INVMEMBERDEPFUNDTYPE        -1800296
#define CM_MEMDEPNOTALLWONACCTYPE      -1800298
#define CM_COLNOTMATCH                 -1800300
#define CM_NOTSAMEPARTICIPANT          -1800302
#define CM_COLSTATEISFINAL             -1800304
#define CM_EXTIDMCEXISTS               -1800306
#define CM_INVCACOMPL                  -1800308
#define CM_INVCASTATE                  -1800310
#define CM_INVCAREF                    -1800312
#define CM_INVCOLRECTYPE               -1800314
#define CM_INVCAITEMS                  -1800316
#define CM_NOTENOUGHBALANCE            -1800318
#define CM_ILLCOLLTRANSTYPE            -1800320
#define CM_CACOMPLEXISTS               -1800322
#define CM_MULTIPLESERIESFORISIN       -1800324
#define CM_CACOMPLMISSING              -1800326
#define CM_PAYINSTNOTPAID              -1800328
#define CM_PAYINSTNOTREVERSED          -1800330
#define CM_ILLINSTRREF                 -1800331
#define CM_DUPBASECOLLREQNOTALLOWED    -1800332
#define CM_SAMESSIID                   -1800334
#define CM_ITTWOACCIDSREQUIRED         -1800336
#define CM_INVITTRANTYPE               -1800338
#define CM_NOWITHDRAWEXPERIOD          -1800340
#define CM_ITAMOUNTDIFF                -1800342
#define CM_ITINSTRREFDIFF              -1800344
#define CM_CANOTUNIQ                   -1800346
#define CM_CAINVFACTOR                 -1800348
#define CM_INVCOLGROUP                 -1800349
#define CM_INVACCFORSERIES             -1800350
#define CM_VGNOTALLOWEDONACCTYPE       -1800352
#define CM_INVINTERESTITEMS            -1800354
#define CM_NOEXTACC                    -1800356
#define CM_INVCREATEDDDC               -1800358
#define CM_INVCOLLPAYMENTSTATE         -1800360
#define CM_INVEVALUTIONTYPE            -1800362
#define CM_COLLEVALUATIONNOTFOUND      -1800364
#define CM_COLLPAYMENTSALRDYREJECTED   -1800366
#define CM_COLLPAYMENTSALRDYCONFIRMED  -1800368
#define CM_COLLPAYMENTSTATENOTCREATED  -1800370
#define CM_UNCONFIRMEDPAYMENTSEXIST    -1800372
#define CM_COLLTYPENOTPAYMENT          -1800374
#define CM_NODEFCURRENCYRANKING        -1800376
#define CM_ACCCOLLHANDLINGNOTCMSDDDC   -1800378
#define CM_PENDINGDEPOSITCASHEXISTS    -1800380
#define CM_INVACCCMPROP                -1800381
#define CM_CLHMBRBICBLANK              -1800382
#define CM_INVMEMBERDEPITEMS           -1800384
#define CM_TXNTYPENOTCOL               -1800386
#define CM_INVFROMSTATE                -1800388
#define CM_CUTOFFTIMEPASSED            -1800390
#define CM_INVTRIGGERNEWMARGIN         -1800392
#define CM_SENDSWIFTDISALLOWED         -1800394
#define CM_SENDSWIFTREQUIRED           -1800396
#define CM_EXCEEDCONCLIMIT             -1800398
#define CM_ALREADYEXISTS               -1800400
#define CM_ALREADYDELETED              -1800402
#define CM_NOTHINGTORECTIFY            -1800404
#define CM_INVALIDOPERATION            -1800406
#define CM_INVALIDSSITYPE              -1800408
#define CM_INVALIDTAXCODE              -1800410
#define CM_INVSSITYPE                  -1800412
#define CM_INVBANKCODE                 -1800414
#define CM_INVBIC                      -1800416
#define CM_INVABANUMBER                -1800418
#define CM_INVISINTERNAL               -1800420
#define CM_CHGSSIIDNOTALLOWED          -1800422
#define CM_CHGCURRENCYNOTALLOWED       -1800424
#define CM_INVTAXCODE                  -1800426
#define CM_SSINOTFOUND                 -1800428
#define CM_INVSSIID                    -1800430
#define CM_CLHACCIDBLANK               -1800432
#define CM_CHGBICNOTALLOWED            -1800434
#define CM_CHGACCNUMBERNOTALLOWED      -1800436
#define CM_ALLABANUMBERNOTEQUAL        -1800438
#define CM_EXPSTRUCTNOTFOUND           -1800440
#define CM_SSIREFDIFFCLHACCOUNTS       -1800442
#define CM_CLHACCOUNTSSIMISMATCH       -1800444
#define CM_INVISIN                     -1800446
#define CM_ACTIVECABATCHEXIST          -1800448
#define CM_ACTIVECATXNEXIST            -1800450
#define CM_INVACCOUNTNUMBER            -1800452
#define CM_INVACCOUNTNAME              -1800454
#define CM_CLHACCOUNTIDNOTALLOWED      -1800456
#define CM_INVCLHACCOUNTONLY           -1800458
#define CM_CLHACCOUNTNOTFOUND          -1800460
#define CM_NOCOLLATERALHANDLING        -1800462
#define CM_INVCLHACCOUNTID             -1800464
#define CM_SSIIDNOTALLOWED             -1800466
#define CM_ACCNODEPOSITINTEREST        -1800468
#define CM_ACCNOWITHDRAWINTEREST       -1800470
#define CM_COLLHANDLINGNOTCASHSTTLMNT  -1800472
#define CM_NOSETTLEMENTDATE            -1800474
#define CM_NOCOLLSETDATE               -1800476
#define CM_GUARANTEENOTALLOWED         -1800478
#define CM_ACCNOTALLOWINTEREST         -1800480
#define CM_ITSAMEACCOUNT               -1800482
#define CM_ILLCOLLTRANSSTATE           -1800484
#define CM_MUSTBEBLANKINSTTREF         -1800486
#define CM_CLOSEDFORSETTLEMENT         -1800488
#define CM_SSIINSTTYPEREQ              -1800490
#define CM_INVSSIINSTTYPE              -1800492
#define CM_NOEODEVALWITHPAYMENT        -1800494
#define CM_BATCHFAILED                 -1800496
#define CM_COLLTRANSMODIFIED           -1800498
#define CM_SWIFTMESTYPENOTSETBYGSG     -1800500
#define CM_GSGCOLNOTMATCH              -1800502
#define CM_MWANOTENOUGHBALANCE         -1800504
#define CM_MWAREMCOLLEQUALTOBALANCE    -1800506
#define CM_MWAREMCOLLMORETHANBALANCE   -1800508
#define CM_MWAACCOUNTNOTINSURPLUS      -1800510
#define CM_MWACALCULATIONFAILED        -1800512
#define CM_MWAEQUALTOZERO              -1800514
#define CM_MWAREMCOLLPOSORZERO         -1800516
#define CM_MWAREQREMNOTALL             -1800518
#define CM_MWAREQREMNOTALLPER          -1800520
#define CM_MWAINVREMTYPE               -1800522
#define CM_MDF_VERSION                  1819999

/******************************************************************************
*end*of* cm_messages.h
*******************************************************************************/

#endif /* _CM_MESSAGES_H_ */


#ifndef _CX_MESSAGES_H_
#define _CX_MESSAGES_H_

/******************************************************************************
Module: cx_messages.h

Message definitions generated 2020-10-21 15:24:30 by amt, version 3.19.7.0 - Built: 2017-12-30.

NOTE: Do not edit this file. It is automatically generated from
      one or more message files.
*******************************************************************************/

#define CX_NORMAL                       1700001
#define CX_TXALRDHDL                    1700003
#define CX_UNKNOWNEVENT                -1700004
#define CX_INVTRANSSIZE                -1700006
#define CX_INVTRANSTYPE                -1700008
#define CX_INTERNALERROR               -1700009
#define CX_INVUSER                     -1700011
#define CX_INVTX                       -1700013
#define CX_INVSEGMENTNR                -1700015
#define CX_INSFMEM                     -1700016
#define CX_BUGCHECK                    -1700018
#define CX_ABORT                       -1700020
#define CX_SQLERROR                    -1700022
#define CX_CARRYMISSING                -1700024
#define CX_TOMANYCARRYLEG              -1700026
#define CX_LABELNOTFOUND               -1700028
#define CX_COMPLETED                    1700029
#define CX_CMD_QUEUE                    1700031
#define CX_OBJECT_FULL                 -1700032
#define CX_DEL_IMBALANCE               -1700034
#define CX_MQ_SENDMSG_FAILED           -1700036
#define CX_MQ_RECEIVEMSG_FAILED        -1700038
#define CX_MQ_CONNECTION_BROKEN        -1700040
#define CX_BNK_IMBALANCE               -1700042
#define CX_MARGIN_IMBALANCE            -1700044
#define CX_NORPTLCHMEMBER              -1700046
#define CX_DISCONNECT                  -1700047
#define CX_OK                           1700049
#define CX_RTR_ERROR                   -1700050
#define CX_SRVREJECT                   -1700051
#define CX_NOSRVAVAIL                  -1700053
#define CX_PROTOCOLERRE                -1700054
#define CX_INVCOUNTRY                  -1700056
#define CX_DB_LOCKED                   -1700058
#define CX_INVTXCONTENT                -1700060
#define CX_NEXISTORDER                 -1700062
#define CX_INVORDERSTATE               -1700064
#define CX_INVCHANGESTATE              -1700066
#define CX_INVTXDATA                   -1700068
#define CX_LOGIC                       -1700069
#define CX_REMOTE_ACCEPT                1700071
#define CX_REMOTE_REJECT               -1700073
#define CX_INVSERIES                   -1700074
#define CX_HASH_INSERT                 -1700076
#define CX_CONFIG_EXCEPTION            -1700078
#define CX_SEND_FAILED                 -1700080
#define CX_QRYTIMEOUT                  -1700082
#define CX_REMPROBLEM                  -1700084
#define CX_REMEXCHANGE                 -1700086
#define CX_REMTRANS                    -1700088
#define CX_INVSTATE                    -1700090
#define CX_CONVERT_ERROR               -1700092
#define CX_TRANSTURNEDOFF               1700093
#define CX_MSGBUFFER_FULL               1700095
#define CX_INVHOST                     -1700096
#define CX_VPCERROR                    -1700098
#define CX_INV_SEQUENCE                -1700100
#define CX_INV_BDATE                   -1700102
#define CX_INV_ACCOUNT                 -1700104
#define CX_INV_CALCTYPE                -1700106
#define CX_INV_CLEARINGDATE            -1700108
#define CX_INV_SERIES                  -1700110
#define CX_INV_ENDOFDATE               -1700112
#define CX_INV_CURVE_DATE              -1700114
#define CX_CURVE_UNAVAIL               -1700116
#define CX_INV_SEGMENT_NUMBER          -1700118
#define CX_INV_JOB_NAME                -1700120
#define CX_INV_TASK_SPEC               -1700122
#define CX_AUT_ALREADY_FINAL            1700123
#define CX_AUT_SAME_USER               -1700124
#define CX_AUT_NOT_ALLOWED             -1700126
#define CX_AUT_UNKNOWN_TX              -1700128
#define CX_INV_INT_SETTL_FROM_DATE     -1700130
#define CX_INV_INT_SETTL_TO_DATE       -1700132
#define CX_INV_ACC_KEEPER_ID           -1700134
#define CX_INV_INVESTOR_ACC            -1700136
#define CX_INV_FIRST_VALID_DATE        -1700138
#define CX_INV_LAST_VALID_DATE         -1700140
#define CX_INV_INT_SETTL_DATE          -1700142
#define CX_INV_TRADE_DATE              -1700144
#define CX_MDF_VERSION                  1710001

/******************************************************************************
*end*of* cx_messages.h
*******************************************************************************/

#endif /* _CX_MESSAGES_H_ */


#ifndef _XCSD_MESSAGES_H_
#define _XCSD_MESSAGES_H_

/******************************************************************************
Module: xcsd_messages.h

Message definitions generated 2020-10-21 15:24:30 by amt, version 3.19.7.0 - Built: 2017-12-30.

NOTE: Do not edit this file. It is automatically generated from
      one or more message files.
*******************************************************************************/

#define XCSD_MSG1                      -2200002
#define XCSD_MSG2                      -2200004
#define XCSD_MSG3                      -2200006
#define XCSD_MSG4                      -2200008
#define XCSD_MSG5                      -2200010
#define XCSD_MSG6                      -2200012
#define XCSD_MSG7                      -2200014
#define XCSD_MSG8                      -2200016
#define XCSD_MSG9                      -2200018
#define XCSD_MSG10                     -2200020
#define XCSD_MSG11                     -2200022
#define XCSD_MSG12                     -2200024
#define XCSD_MSG13                     -2200026
#define XCSD_MSG14                     -2200028
#define XCSD_MSG15                     -2200030
#define XCSD_MSG16                     -2200032
#define XCSD_MSG17                     -2200034
#define XCSD_MSG18                     -2200036
#define XCSD_MSG19                     -2200038
#define XCSD_MSG20                     -2200040
#define XCSD_MSG21                     -2200042
#define XCSD_MSG22                     -2200044
#define XCSD_MSG23                     -2200046
#define XCSD_MSG24                     -2200048
#define XCSD_MSG25                     -2200050
#define XCSD_MSG26                     -2200052
#define XCSD_MSG27                     -2200054
#define XCSD_MSG28                     -2200056
#define XCSD_MSG29                     -2200058
#define XCSD_MSG30                     -2200060
#define XCSD_MSG31                     -2200062
#define XCSD_MSG32                     -2200064
#define XCSD_MSG33                     -2200066
#define XCSD_MSG34                     -2200068
#define XCSD_MSG35                     -2200070
#define XCSD_MSG36                     -2200072
#define XCSD_MSG37                     -2200074
#define XCSD_MSG38                     -2200076
#define XCSD_MSG39                     -2200078
#define XCSD_MSG40                     -2200080
#define XCSD_MSG41                     -2200082
#define XCSD_MSG42                     -2200084
#define XCSD_MSG43                     -2200086
#define XCSD_MSG44                     -2200088
#define XCSD_MSG45                     -2200090
#define XCSD_MSG46                     -2200092
#define XCSD_MSG47                     -2200094
#define XCSD_MSG48                     -2200096
#define XCSD_MSG49                     -2200098
#define XCSD_MSG50                     -2200100
#define XCSD_MSG51                     -2200102
#define XCSD_MSG52                     -2200104
#define XCSD_MSG53                     -2200106
#define XCSD_MSG54                     -2200108
#define XCSD_MSG55                     -2200110
#define XCSD_MSG56                     -2200112
#define XCSD_MSG57                     -2200114
#define XCSD_MSG58                     -2200116
#define XCSD_MSG59                     -2200118
#define XCSD_MSG60                     -2200120
#define XCSD_MSG61                     -2200122
#define XCSD_MSG62                     -2200124
#define XCSD_MSG63                     -2200126
#define XCSD_MSG64                     -2200128
#define XCSD_MSG65                     -2200130
#define XCSD_MSG66                     -2200132
#define XCSD_MSG67                     -2200134
#define XCSD_MSG68                     -2200136
#define XCSD_MSG69                     -2200138
#define XCSD_MSG70                     -2200140
#define XCSD_MSG71                     -2200142
#define XCSD_MSG72                     -2200144
#define XCSD_MSG73                     -2200146
#define XCSD_MSG74                     -2200148
#define XCSD_MSG75                     -2200150
#define XCSD_MSG76                     -2200152
#define XCSD_MSG77                     -2200154
#define XCSD_MSG78                     -2200156
#define XCSD_MSG79                     -2200158
#define XCSD_MSG80                     -2200160
#define XCSD_MSG81                     -2200162
#define XCSD_MSG82                     -2200164
#define XCSD_MSG83                     -2200166
#define XCSD_MSG84                     -2200168
#define XCSD_MSG85                     -2200170
#define XCSD_MSG86                     -2200172
#define XCSD_MSG87                     -2200174
#define XCSD_MSG88                     -2200176
#define XCSD_MSG89                     -2200178
#define XCSD_MSG90                     -2200180
#define XCSD_MSG91                     -2200182
#define XCSD_MSG92                     -2200184
#define XCSD_MSG93                     -2200186
#define XCSD_MSG94                     -2200188
#define XCSD_MSG95                     -2200190
#define XCSD_MSG96                     -2200192
#define XCSD_MSG97                     -2200194
#define XCSD_MSG98                     -2200196
#define XCSD_MSG99                     -2200198
#define XCSD_MSG100                    -2200200
#define XCSD_MSG101                    -2200202
#define XCSD_MSG102                    -2200204
#define XCSD_MSG103                    -2200206
#define XCSD_MSG104                    -2200208
#define XCSD_MSG105                    -2200210
#define XCSD_MSG106                    -2200212
#define XCSD_MSG107                    -2200214
#define XCSD_MSG108                    -2200216
#define XCSD_MSG109                    -2200218
#define XCSD_MSG110                    -2200220
#define XCSD_MSG111                    -2200222
#define XCSD_MSG112                    -2200224
#define XCSD_MSG113                    -2200226
#define XCSD_MSG114                    -2200228
#define XCSD_MSG115                    -2200230
#define XCSD_MSG116                    -2200232
#define XCSD_MSG117                    -2200234
#define XCSD_MSG118                    -2200236
#define XCSD_MSG119                    -2200238
#define XCSD_MSG120                    -2200240
#define XCSD_MSG121                    -2200242
#define XCSD_MSG122                    -2200244
#define XCSD_MSG123                    -2200246
#define XCSD_MSG124                    -2200248
#define XCSD_MSG125                    -2200250
#define XCSD_MSG126                    -2200252
#define XCSD_MSG127                    -2200254
#define XCSD_MSG128                    -2200256
#define XCSD_MSG129                    -2200258
#define XCSD_MSG130                    -2200260
#define XCSD_MSG131                    -2200262
#define XCSD_MSG132                    -2200264
#define XCSD_MSG133                    -2200266
#define XCSD_MSG134                    -2200268
#define XCSD_MSG135                    -2200270
#define XCSD_MSG136                    -2200272
#define XCSD_MSG137                    -2200274
#define XCSD_MSG138                    -2200276
#define XCSD_MSG139                    -2200278
#define XCSD_MSG140                    -2200280
#define XCSD_MSG141                    -2200282
#define XCSD_MSG142                    -2200284
#define XCSD_MSG143                    -2200286
#define XCSD_MSG144                    -2200288
#define XCSD_MSG145                    -2200290
#define XCSD_MSG146                    -2200292
#define XCSD_MSG147                    -2200294
#define XCSD_MSG148                    -2200296
#define XCSD_MSG149                    -2200298
#define XCSD_MSG150                    -2200300
#define XCSD_MSG151                    -2200302
#define XCSD_MSG152                    -2200304
#define XCSD_MSG153                    -2200306
#define XCSD_MSG154                    -2200308
#define XCSD_MSG155                    -2200310
#define XCSD_MSG156                    -2200312
#define XCSD_MSG157                    -2200314
#define XCSD_MSG158                    -2200316
#define XCSD_MSG159                    -2200318
#define XCSD_MSG160                    -2200320
#define XCSD_MSG161                    -2200322
#define XCSD_MSG162                    -2200324
#define XCSD_MSG163                    -2200326
#define XCSD_MSG164                    -2200328
#define XCSD_MSG165                    -2200330
#define XCSD_MSG166                    -2200332
#define XCSD_MSG167                    -2200334
#define XCSD_MSG168                    -2200336
#define XCSD_MSG169                    -2200338
#define XCSD_MSG170                    -2200340
#define XCSD_MSG171                    -2200342
#define XCSD_MSG172                    -2200344
#define XCSD_MSG173                    -2200346
#define XCSD_MSG174                    -2200348
#define XCSD_MSG175                    -2200350
#define XCSD_MSG176                    -2200352
#define XCSD_MSG177                    -2200354
#define XCSD_MSG178                    -2200356
#define XCSD_MSG179                    -2200358
#define XCSD_MSG180                    -2200360
#define XCSD_MSG181                    -2200362
#define XCSD_MSG182                    -2200364
#define XCSD_MSG183                    -2200366
#define XCSD_MSG184                    -2200368
#define XCSD_MSG185                    -2200370
#define XCSD_MSG186                    -2200372
#define XCSD_MSG187                    -2200374
#define XCSD_MSG188                    -2200376
#define XCSD_MSG189                    -2200378
#define XCSD_MSG190                    -2200380
#define XCSD_MSG191                    -2200382
#define XCSD_MSG192                    -2200384
#define XCSD_MSG193                    -2200386
#define XCSD_MSG194                    -2200388
#define XCSD_MSG195                    -2200390
#define XCSD_MSG196                    -2200392
#define XCSD_MSG197                    -2200394
#define XCSD_MSG198                    -2200396
#define XCSD_MSG199                    -2200398
#define XCSD_MSG200                    -2200400
#define XCSD_MSG201                    -2200402
#define XCSD_MSG202                    -2200404
#define XCSD_MSG203                    -2200406
#define XCSD_MSG204                    -2200408
#define XCSD_MSG205                    -2200410
#define XCSD_MSG206                    -2200412
#define XCSD_MSG207                    -2200414
#define XCSD_MSG208                    -2200416
#define XCSD_MSG209                    -2200418
#define XCSD_MSG210                    -2200420
#define XCSD_MSG211                    -2200422
#define XCSD_MSG212                    -2200424
#define XCSD_MSG213                    -2200426
#define XCSD_MSG214                    -2200428
#define XCSD_MSG215                    -2200430
#define XCSD_MSG216                    -2200432
#define XCSD_MSG217                    -2200434
#define XCSD_MSG218                    -2200436
#define XCSD_MSG219                    -2200438
#define XCSD_MSG220                    -2200440
#define XCSD_MSG221                    -2200442
#define XCSD_MSG222                    -2200444
#define XCSD_MSG223                    -2200446
#define XCSD_MSG224                    -2200448
#define XCSD_MSG225                    -2200450
#define XCSD_MSG226                    -2200452
#define XCSD_MSG227                    -2200454
#define XCSD_MSG228                    -2200456
#define XCSD_MSG229                    -2200458
#define XCSD_MSG230                    -2200460
#define XCSD_MSG231                    -2200462
#define XCSD_MSG232                    -2200464
#define XCSD_MSG233                    -2200466
#define XCSD_MSG234                    -2200468
#define XCSD_MSG235                    -2200470
#define XCSD_MSG236                    -2200472
#define XCSD_MSG237                    -2200474
#define XCSD_MSG238                    -2200476
#define XCSD_MSG239                    -2200478
#define XCSD_MSG240                    -2200480
#define XCSD_MSG241                    -2200482
#define XCSD_MSG242                    -2200484
#define XCSD_MSG243                    -2200486
#define XCSD_MSG244                    -2200488
#define XCSD_MSG245                    -2200490
#define XCSD_MSG246                    -2200492
#define XCSD_MSG247                    -2200494
#define XCSD_MSG248                    -2200496
#define XCSD_MSG249                    -2200498
#define XCSD_MSG250                    -2200500
#define XCSD_MSG251                    -2200502
#define XCSD_MSG252                    -2200504
#define XCSD_MSG253                    -2200506
#define XCSD_MSG254                    -2200508
#define XCSD_MSG255                    -2200510
#define XCSD_MSG256                    -2200512
#define XCSD_MSG257                    -2200514
#define XCSD_MSG258                    -2200516
#define XCSD_MSG259                    -2200518
#define XCSD_MSG260                    -2200520
#define XCSD_MSG261                    -2200522
#define XCSD_MSG262                    -2200524
#define XCSD_MSG263                    -2200526
#define XCSD_MSG264                    -2200528
#define XCSD_MSG265                    -2200530
#define XCSD_MSG266                    -2200532
#define XCSD_MSG267                    -2200534
#define XCSD_MSG268                    -2200536
#define XCSD_MSG269                    -2200538
#define XCSD_MSG270                    -2200540
#define XCSD_MSG271                    -2200542
#define XCSD_MSG272                    -2200544
#define XCSD_MSG273                    -2200546
#define XCSD_MSG274                    -2200548
#define XCSD_MSG275                    -2200550
#define XCSD_MSG276                    -2200552
#define XCSD_MSG277                    -2200554
#define XCSD_MSG278                    -2200556
#define XCSD_MSG279                    -2200558
#define XCSD_MSG280                    -2200560
#define XCSD_MSG281                    -2200562
#define XCSD_MSG282                    -2200564
#define XCSD_MSG283                    -2200566
#define XCSD_MSG284                    -2200568
#define XCSD_MSG285                    -2200570
#define XCSD_MSG286                    -2200572
#define XCSD_MSG287                    -2200574
#define XCSD_MSG288                    -2200576
#define XCSD_MSG289                    -2200578
#define XCSD_MSG290                    -2200580
#define XCSD_MSG291                    -2200582
#define XCSD_MSG292                    -2200584
#define XCSD_MSG293                    -2200586
#define XCSD_MSG294                    -2200588
#define XCSD_MSG295                    -2200590
#define XCSD_MSG296                    -2200592
#define XCSD_MSG297                    -2200594
#define XCSD_MSG298                    -2200596
#define XCSD_MSG299                    -2200598
#define XCSD_MSG300                    -2200600
#define XCSD_MSG301                    -2200602
#define XCSD_MSG302                    -2200604
#define XCSD_MSG303                    -2200606
#define XCSD_MSG304                    -2200608
#define XCSD_MSG305                    -2200610
#define XCSD_MSG306                    -2200612
#define XCSD_MSG307                    -2200614
#define XCSD_MSG308                    -2200616
#define XCSD_MSG309                    -2200618
#define XCSD_MSG310                    -2200620
#define XCSD_MSG311                    -2200622
#define XCSD_MSG312                    -2200624
#define XCSD_MSG313                    -2200626
#define XCSD_MSG314                    -2200628
#define XCSD_MSG315                    -2200630
#define XCSD_MSG316                    -2200632
#define XCSD_MSG317                    -2200634
#define XCSD_MSG318                    -2200636
#define XCSD_MSG319                    -2200638
#define XCSD_MSG320                    -2200640
#define XCSD_MSG321                    -2200642
#define XCSD_MSG322                    -2200644
#define XCSD_MSG323                    -2200646
#define XCSD_MSG324                    -2200648
#define XCSD_MSG325                    -2200650
#define XCSD_MSG326                    -2200652
#define XCSD_MSG327                    -2200654
#define XCSD_MSG328                    -2200656
#define XCSD_MSG329                    -2200658
#define XCSD_MSG330                    -2200660
#define XCSD_MSG331                    -2200662
#define XCSD_MSG332                    -2200664
#define XCSD_MSG333                    -2200666
#define XCSD_MSG334                    -2200668
#define XCSD_MSG335                    -2200670
#define XCSD_MSG336                    -2200672
#define XCSD_MSG337                    -2200674
#define XCSD_MSG338                    -2200676
#define XCSD_MSG339                    -2200678
#define XCSD_MSG340                    -2200680
#define XCSD_MSG341                    -2200682
#define XCSD_MSG342                    -2200684
#define XCSD_MSG343                    -2200686
#define XCSD_MSG344                    -2200688
#define XCSD_MSG345                    -2200690
#define XCSD_MSG346                    -2200692
#define XCSD_MSG347                    -2200694
#define XCSD_MSG348                    -2200696
#define XCSD_MSG349                    -2200698
#define XCSD_MSG350                    -2200700
#define XCSD_MSG351                    -2200702
#define XCSD_MSG352                    -2200704
#define XCSD_MSG353                    -2200706
#define XCSD_MSG354                    -2200708
#define XCSD_MSG355                    -2200710
#define XCSD_MSG356                    -2200712
#define XCSD_MSG357                    -2200714
#define XCSD_MSG358                    -2200716
#define XCSD_MSG359                    -2200718
#define XCSD_MSG360                    -2200720
#define XCSD_MSG361                    -2200722
#define XCSD_MSG362                    -2200724
#define XCSD_MSG363                    -2200726
#define XCSD_MSG364                    -2200728
#define XCSD_MSG365                    -2200730
#define XCSD_MSG366                    -2200732
#define XCSD_MSG367                    -2200734
#define XCSD_MSG368                    -2200736
#define XCSD_MSG369                    -2200738
#define XCSD_MSG370                    -2200740
#define XCSD_MSG371                    -2200742
#define XCSD_MSG372                    -2200744
#define XCSD_MSG373                    -2200746
#define XCSD_MSG374                    -2200748
#define XCSD_MSG375                    -2200750
#define XCSD_MSG376                    -2200752
#define XCSD_MSG377                    -2200754
#define XCSD_MSG378                    -2200756
#define XCSD_MSG379                    -2200758
#define XCSD_MSG380                    -2200760
#define XCSD_MSG381                    -2200762
#define XCSD_MSG382                    -2200764
#define XCSD_MSG383                    -2200766
#define XCSD_MSG384                    -2200768
#define XCSD_MSG385                    -2200770
#define XCSD_MSG386                    -2200772
#define XCSD_MSG387                    -2200774
#define XCSD_MSG388                    -2200776
#define XCSD_MSG389                    -2200778
#define XCSD_MSG390                    -2200780
#define XCSD_MSG391                    -2200782
#define XCSD_MSG392                    -2200784
#define XCSD_MSG393                    -2200786
#define XCSD_MSG394                    -2200788
#define XCSD_MSG395                    -2200790
#define XCSD_MSG396                    -2200792
#define XCSD_MSG397                    -2200794
#define XCSD_MSG398                    -2200796
#define XCSD_MSG399                    -2200798
#define XCSD_MSG400                    -2200800
#define XCSD_MSG401                    -2200802
#define XCSD_MSG402                    -2200804
#define XCSD_MSG403                    -2200806
#define XCSD_MSG404                    -2200808
#define XCSD_MSG405                    -2200810
#define XCSD_MSG406                    -2200812
#define XCSD_MSG407                    -2200814
#define XCSD_MSG408                    -2200816
#define XCSD_MSG409                    -2200818
#define XCSD_MSG410                    -2200820
#define XCSD_MSG411                    -2200822
#define XCSD_MSG412                    -2200824
#define XCSD_MSG413                    -2200826
#define XCSD_MSG414                    -2200828
#define XCSD_MSG415                    -2200830
#define XCSD_MSG416                    -2200832
#define XCSD_MSG417                    -2200834
#define XCSD_MSG418                    -2200836
#define XCSD_MSG419                    -2200838
#define XCSD_MSG420                    -2200840
#define XCSD_MSG421                    -2200842
#define XCSD_MSG422                    -2200844
#define XCSD_MSG423                    -2200846
#define XCSD_MSG424                    -2200848
#define XCSD_MSG425                    -2200850
#define XCSD_MSG426                    -2200852
#define XCSD_MSG427                    -2200854
#define XCSD_MSG428                    -2200856
#define XCSD_MSG429                    -2200858
#define XCSD_MSG430                    -2200860
#define XCSD_MSG431                    -2200862
#define XCSD_MSG432                    -2200864
#define XCSD_MSG433                    -2200866
#define XCSD_MSG434                    -2200868
#define XCSD_MSG435                    -2200870
#define XCSD_MSG436                    -2200872
#define XCSD_MSG437                    -2200874
#define XCSD_MSG438                    -2200876
#define XCSD_MSG439                    -2200878
#define XCSD_MSG440                    -2200880
#define XCSD_MSG441                    -2200882
#define XCSD_MSG442                    -2200884
#define XCSD_MSG443                    -2200886
#define XCSD_MSG444                    -2200888
#define XCSD_MSG445                    -2200890
#define XCSD_MSG446                    -2200892
#define XCSD_MSG447                    -2200894
#define XCSD_MSG448                    -2200896
#define XCSD_MSG449                    -2200898
#define XCSD_MSG450                    -2200900
#define XCSD_MSG451                    -2200902
#define XCSD_MSG452                    -2200904
#define XCSD_MSG453                    -2200906
#define XCSD_MSG454                    -2200908
#define XCSD_MSG455                    -2200910
#define XCSD_MSG456                    -2200912
#define XCSD_MSG457                    -2200914
#define XCSD_MSG458                    -2200916
#define XCSD_MSG459                    -2200918
#define XCSD_MSG460                    -2200920
#define XCSD_MSG461                    -2200922
#define XCSD_MSG462                    -2200924
#define XCSD_MSG463                    -2200926
#define XCSD_MSG464                    -2200928
#define XCSD_MSG465                    -2200930
#define XCSD_MSG466                    -2200932
#define XCSD_MSG467                    -2200934
#define XCSD_MSG468                    -2200936
#define XCSD_MSG469                    -2200938
#define XCSD_MSG470                    -2200940
#define XCSD_MSG471                    -2200942
#define XCSD_MSG472                    -2200944
#define XCSD_MSG473                    -2200946
#define XCSD_MSG474                    -2200948
#define XCSD_MSG475                    -2200950
#define XCSD_MSG476                    -2200952
#define XCSD_MSG477                    -2200954
#define XCSD_MSG478                    -2200956
#define XCSD_MSG479                    -2200958
#define XCSD_MSG480                    -2200960
#define XCSD_MSG481                    -2200962
#define XCSD_MSG482                    -2200964
#define XCSD_MSG483                    -2200966
#define XCSD_MSG484                    -2200968
#define XCSD_MSG485                    -2200970
#define XCSD_MSG486                    -2200972
#define XCSD_MSG487                    -2200974
#define XCSD_MSG488                    -2200976
#define XCSD_MSG489                    -2200978
#define XCSD_MSG490                    -2200980
#define XCSD_MSG491                    -2200982
#define XCSD_MSG492                    -2200984
#define XCSD_MSG493                    -2200986
#define XCSD_MSG494                    -2200988
#define XCSD_MSG495                    -2200990
#define XCSD_MSG496                    -2200992
#define XCSD_MSG497                    -2200994
#define XCSD_MSG498                    -2200996
#define XCSD_MSG499                    -2200998
#define XCSD_MSG500                    -2201000
#define XCSD_MSG501                    -2201002
#define XCSD_MSG502                    -2201004
#define XCSD_MSG503                    -2201006
#define XCSD_MSG504                    -2201008
#define XCSD_MSG505                    -2201010
#define XCSD_MSG506                    -2201012
#define XCSD_MSG507                    -2201014
#define XCSD_MSG508                    -2201016
#define XCSD_MSG509                    -2201018
#define XCSD_MSG510                    -2201020
#define XCSD_MSG511                    -2201022
#define XCSD_MSG512                    -2201024
#define XCSD_MSG513                    -2201026
#define XCSD_MSG514                    -2201028
#define XCSD_MSG515                    -2201030
#define XCSD_MSG516                    -2201032
#define XCSD_MSG517                    -2201034
#define XCSD_MSG518                    -2201036
#define XCSD_MSG519                    -2201038
#define XCSD_MSG520                    -2201040
#define XCSD_MSG521                    -2201042
#define XCSD_MSG522                    -2201044
#define XCSD_MSG523                    -2201046
#define XCSD_MSG524                    -2201048
#define XCSD_MSG525                    -2201050
#define XCSD_MSG526                    -2201052
#define XCSD_MSG527                    -2201054
#define XCSD_MSG528                    -2201056
#define XCSD_MSG529                    -2201058
#define XCSD_MSG530                    -2201060
#define XCSD_MSG531                    -2201062
#define XCSD_MSG532                    -2201064
#define XCSD_MSG533                    -2201066
#define XCSD_MSG534                    -2201068
#define XCSD_MSG535                    -2201070
#define XCSD_MSG536                    -2201072
#define XCSD_MSG537                    -2201074
#define XCSD_MSG538                    -2201076
#define XCSD_MSG539                    -2201078
#define XCSD_MSG540                    -2201080
#define XCSD_MSG541                    -2201082
#define XCSD_MSG542                    -2201084
#define XCSD_MSG543                    -2201086
#define XCSD_MSG544                    -2201088
#define XCSD_MSG545                    -2201090
#define XCSD_MSG546                    -2201092
#define XCSD_MSG547                    -2201094
#define XCSD_MSG548                    -2201096
#define XCSD_MSG549                    -2201098
#define XCSD_MSG550                    -2201100
#define XCSD_MSG551                    -2201102
#define XCSD_MSG552                    -2201104
#define XCSD_MSG553                    -2201106
#define XCSD_MSG554                    -2201108
#define XCSD_MSG555                    -2201110
#define XCSD_MSG556                    -2201112
#define XCSD_MSG557                    -2201114
#define XCSD_MSG558                    -2201116
#define XCSD_MSG559                    -2201118
#define XCSD_MSG560                    -2201120
#define XCSD_MSG561                    -2201122
#define XCSD_MSG562                    -2201124
#define XCSD_MSG563                    -2201126
#define XCSD_MSG564                    -2201128
#define XCSD_MSG565                    -2201130
#define XCSD_MSG566                    -2201132
#define XCSD_MSG567                    -2201134
#define XCSD_MSG568                    -2201136
#define XCSD_MSG569                    -2201138
#define XCSD_MSG570                    -2201140
#define XCSD_MSG571                    -2201142
#define XCSD_MSG572                    -2201144
#define XCSD_MSG573                    -2201146
#define XCSD_MSG574                    -2201148
#define XCSD_MSG575                    -2201150
#define XCSD_MSG576                    -2201152
#define XCSD_MSG577                    -2201154
#define XCSD_MSG578                    -2201156
#define XCSD_MSG579                    -2201158
#define XCSD_MSG580                    -2201160
#define XCSD_MSG581                    -2201162
#define XCSD_MSG582                    -2201164
#define XCSD_MSG583                    -2201166
#define XCSD_MSG584                    -2201168
#define XCSD_MSG585                    -2201170
#define XCSD_MSG586                    -2201172
#define XCSD_MSG587                    -2201174
#define XCSD_MSG588                    -2201176
#define XCSD_MSG589                    -2201178
#define XCSD_MSG590                    -2201180
#define XCSD_MSG591                    -2201182
#define XCSD_MSG592                    -2201184
#define XCSD_MSG593                    -2201186
#define XCSD_MSG594                    -2201188
#define XCSD_MSG595                    -2201190
#define XCSD_MSG596                    -2201192
#define XCSD_MSG597                    -2201194
#define XCSD_MSG598                    -2201196
#define XCSD_MSG599                    -2201198
#define XCSD_MSG600                    -2201200
#define XCSD_MSG601                    -2201202
#define XCSD_MSG602                    -2201204
#define XCSD_MSG603                    -2201206
#define XCSD_MSG604                    -2201208
#define XCSD_MSG605                    -2201210
#define XCSD_MSG606                    -2201212
#define XCSD_MSG607                    -2201214
#define XCSD_MSG608                    -2201216
#define XCSD_MSG609                    -2201218
#define XCSD_MSG610                    -2201220
#define XCSD_MSG611                    -2201222
#define XCSD_MSG612                    -2201224
#define XCSD_MSG613                    -2201226
#define XCSD_MSG614                    -2201228
#define XCSD_MSG615                    -2201230
#define XCSD_MSG616                    -2201232
#define XCSD_MSG617                    -2201234
#define XCSD_MSG618                    -2201236
#define XCSD_MSG619                    -2201238
#define XCSD_MSG620                    -2201240
#define XCSD_MSG621                    -2201242
#define XCSD_MSG622                    -2201244
#define XCSD_MSG623                    -2201246
#define XCSD_MSG624                    -2201248
#define XCSD_MSG625                    -2201250
#define XCSD_MSG626                    -2201252
#define XCSD_MSG627                    -2201254
#define XCSD_MSG628                    -2201256
#define XCSD_MSG629                    -2201258
#define XCSD_MSG630                    -2201260
#define XCSD_MSG631                    -2201262
#define XCSD_MSG632                    -2201264
#define XCSD_MSG633                    -2201266
#define XCSD_MSG634                    -2201268
#define XCSD_MSG635                    -2201270
#define XCSD_MSG636                    -2201272
#define XCSD_MSG637                    -2201274
#define XCSD_MSG638                    -2201276
#define XCSD_MSG639                    -2201278
#define XCSD_MSG640                    -2201280
#define XCSD_MSG641                    -2201282
#define XCSD_MSG642                    -2201284
#define XCSD_MSG643                    -2201286
#define XCSD_MSG644                    -2201288
#define XCSD_MSG645                    -2201290
#define XCSD_MSG646                    -2201292
#define XCSD_MSG647                    -2201294
#define XCSD_MSG648                    -2201296
#define XCSD_MSG649                    -2201298
#define XCSD_MSG650                    -2201300
#define XCSD_MSG651                    -2201302
#define XCSD_MSG652                    -2201304
#define XCSD_MSG653                    -2201306
#define XCSD_MSG654                    -2201308
#define XCSD_MSG655                    -2201310
#define XCSD_MSG656                    -2201312
#define XCSD_MSG657                    -2201314
#define XCSD_MSG658                    -2201316
#define XCSD_MSG659                    -2201318
#define XCSD_MSG660                    -2201320
#define XCSD_MSG661                    -2201322
#define XCSD_MSG662                    -2201324
#define XCSD_MSG663                    -2201326
#define XCSD_MSG664                    -2201328
#define XCSD_MSG665                    -2201330
#define XCSD_MSG666                    -2201332
#define XCSD_MSG667                    -2201334
#define XCSD_MSG668                    -2201336
#define XCSD_MSG669                    -2201338
#define XCSD_MSG670                    -2201340
#define XCSD_MSG671                    -2201342
#define XCSD_MSG672                    -2201344
#define XCSD_MSG673                    -2201346
#define XCSD_MSG674                    -2201348
#define XCSD_MSG675                    -2201350
#define XCSD_MSG676                    -2201352
#define XCSD_MSG677                    -2201354
#define XCSD_MSG678                    -2201356
#define XCSD_MSG679                    -2201358
#define XCSD_MSG680                    -2201360
#define XCSD_MSG681                    -2201362
#define XCSD_MSG682                    -2201364
#define XCSD_MSG683                    -2201366
#define XCSD_MSG684                    -2201368
#define XCSD_MSG685                    -2201370
#define XCSD_MSG686                    -2201372
#define XCSD_MSG687                    -2201374
#define XCSD_MSG688                    -2201376
#define XCSD_MSG689                    -2201378
#define XCSD_MSG690                    -2201380
#define XCSD_MSG691                    -2201382
#define XCSD_MSG692                    -2201384
#define XCSD_MSG693                    -2201386
#define XCSD_MSG694                    -2201388
#define XCSD_MSG695                    -2201390
#define XCSD_MSG696                    -2201392
#define XCSD_MSG697                    -2201394
#define XCSD_MSG698                    -2201396
#define XCSD_MSG699                    -2201398
#define XCSD_MSG700                    -2201400
#define XCSD_MSG701                    -2201402
#define XCSD_MSG702                    -2201404
#define XCSD_MSG703                    -2201406
#define XCSD_MSG704                    -2201408
#define XCSD_MSG705                    -2201410
#define XCSD_MSG706                    -2201412
#define XCSD_MSG707                    -2201414
#define XCSD_MSG708                    -2201416
#define XCSD_MSG709                    -2201418
#define XCSD_MSG710                    -2201420
#define XCSD_MSG711                    -2201422
#define XCSD_MSG712                    -2201424
#define XCSD_MSG713                    -2201426
#define XCSD_MSG714                    -2201428
#define XCSD_MSG715                    -2201430
#define XCSD_MSG716                    -2201432
#define XCSD_MSG717                    -2201434
#define XCSD_MSG718                    -2201436
#define XCSD_MSG719                    -2201438
#define XCSD_MSG720                    -2201440
#define XCSD_MSG721                    -2201442
#define XCSD_MSG722                    -2201444
#define XCSD_MSG723                    -2201446
#define XCSD_MSG724                    -2201448
#define XCSD_MSG725                    -2201450
#define XCSD_MSG726                    -2201452
#define XCSD_MSG727                    -2201454
#define XCSD_MSG728                    -2201456
#define XCSD_MSG729                    -2201458
#define XCSD_MSG730                    -2201460
#define XCSD_MSG731                    -2201462
#define XCSD_MSG732                    -2201464
#define XCSD_MSG733                    -2201466
#define XCSD_MSG734                    -2201468
#define XCSD_MSG735                    -2201470
#define XCSD_MSG736                    -2201472
#define XCSD_MSG737                    -2201474
#define XCSD_MSG738                    -2201476
#define XCSD_MSG739                    -2201478
#define XCSD_MSG740                    -2201480
#define XCSD_MSG741                    -2201482
#define XCSD_MSG742                    -2201484
#define XCSD_MSG743                    -2201486
#define XCSD_MSG744                    -2201488
#define XCSD_MSG745                    -2201490
#define XCSD_MSG746                    -2201492
#define XCSD_MSG747                    -2201494
#define XCSD_MSG748                    -2201496
#define XCSD_MSG749                    -2201498
#define XCSD_MSG750                    -2201500
#define XCSD_MSG751                    -2201502
#define XCSD_MSG752                    -2201504
#define XCSD_MSG753                    -2201506
#define XCSD_MSG754                    -2201508
#define XCSD_MSG755                    -2201510
#define XCSD_MSG756                    -2201512
#define XCSD_MSG757                    -2201514
#define XCSD_MSG758                    -2201516
#define XCSD_MSG759                    -2201518
#define XCSD_MSG760                    -2201520
#define XCSD_MSG761                    -2201522
#define XCSD_MSG762                    -2201524
#define XCSD_MSG763                    -2201526
#define XCSD_MSG764                    -2201528
#define XCSD_MSG765                    -2201530
#define XCSD_MSG766                    -2201532
#define XCSD_MSG767                    -2201534
#define XCSD_MSG768                    -2201536
#define XCSD_MSG769                    -2201538
#define XCSD_MSG770                    -2201540
#define XCSD_MSG771                    -2201542
#define XCSD_MSG772                    -2201544
#define XCSD_MSG773                    -2201546
#define XCSD_MSG774                    -2201548
#define XCSD_MSG775                    -2201550
#define XCSD_MSG776                    -2201552
#define XCSD_MSG777                    -2201554
#define XCSD_MSG778                    -2201556
#define XCSD_MSG779                    -2201558
#define XCSD_MSG780                    -2201560
#define XCSD_MSG781                    -2201562
#define XCSD_MSG782                    -2201564
#define XCSD_MSG783                    -2201566
#define XCSD_MSG784                    -2201568
#define XCSD_MSG785                    -2201570
#define XCSD_MSG786                    -2201572
#define XCSD_MSG787                    -2201574
#define XCSD_MSG788                    -2201576
#define XCSD_MSG789                    -2201578
#define XCSD_MSG790                    -2201580
#define XCSD_MSG791                    -2201582
#define XCSD_MSG792                    -2201584
#define XCSD_MSG793                    -2201586
#define XCSD_MSG794                    -2201588
#define XCSD_MSG795                    -2201590
#define XCSD_MSG796                    -2201592
#define XCSD_MSG797                    -2201594
#define XCSD_MSG798                    -2201596
#define XCSD_MSG799                    -2201598
#define XCSD_MSG800                    -2201600
#define XCSD_MSG801                    -2201602
#define XCSD_MSG802                    -2201604
#define XCSD_MSG803                    -2201606
#define XCSD_MSG804                    -2201608
#define XCSD_MSG805                    -2201610
#define XCSD_MSG806                    -2201612
#define XCSD_MSG807                    -2201614
#define XCSD_MSG808                    -2201616
#define XCSD_MSG809                    -2201618
#define XCSD_MSG810                    -2201620
#define XCSD_MSG811                    -2201622
#define XCSD_MSG812                    -2201624
#define XCSD_MSG813                    -2201626
#define XCSD_MSG814                    -2201628
#define XCSD_MSG815                    -2201630
#define XCSD_MSG816                    -2201632
#define XCSD_MSG817                    -2201634
#define XCSD_MSG818                    -2201636
#define XCSD_MSG819                    -2201638
#define XCSD_MSG820                    -2201640
#define XCSD_MSG821                    -2201642
#define XCSD_MSG822                    -2201644
#define XCSD_MSG823                    -2201646
#define XCSD_MSG824                    -2201648
#define XCSD_MSG825                    -2201650
#define XCSD_MSG826                    -2201652
#define XCSD_MSG827                    -2201654
#define XCSD_MSG828                    -2201656
#define XCSD_MSG829                    -2201658
#define XCSD_MSG830                    -2201660
#define XCSD_MSG831                    -2201662
#define XCSD_MSG832                    -2201664
#define XCSD_MSG833                    -2201666
#define XCSD_MSG834                    -2201668
#define XCSD_MSG835                    -2201670
#define XCSD_MSG836                    -2201672
#define XCSD_MSG837                    -2201674
#define XCSD_MSG838                    -2201676
#define XCSD_MSG839                    -2201678
#define XCSD_MSG840                    -2201680
#define XCSD_MSG841                    -2201682
#define XCSD_MSG842                    -2201684
#define XCSD_MSG843                    -2201686
#define XCSD_MSG844                    -2201688
#define XCSD_MSG845                    -2201690
#define XCSD_MSG846                    -2201692
#define XCSD_MSG847                    -2201694
#define XCSD_MSG848                    -2201696
#define XCSD_MSG849                    -2201698
#define XCSD_MSG850                    -2201700
#define XCSD_MSG851                    -2201702
#define XCSD_MSG852                    -2201704
#define XCSD_MSG853                    -2201706
#define XCSD_MSG854                    -2201708
#define XCSD_MSG855                    -2201710
#define XCSD_MSG856                    -2201712
#define XCSD_MSG857                    -2201714
#define XCSD_MSG858                    -2201716
#define XCSD_MSG859                    -2201718
#define XCSD_MSG860                    -2201720
#define XCSD_MSG861                    -2201722
#define XCSD_MSG862                    -2201724
#define XCSD_MSG863                    -2201726
#define XCSD_MSG864                    -2201728
#define XCSD_MSG865                    -2201730
#define XCSD_MSG866                    -2201732
#define XCSD_MSG867                    -2201734
#define XCSD_MSG868                    -2201736
#define XCSD_MSG869                    -2201738
#define XCSD_MSG870                    -2201740
#define XCSD_MSG871                    -2201742
#define XCSD_MSG872                    -2201744
#define XCSD_MSG873                    -2201746
#define XCSD_MSG874                    -2201748
#define XCSD_MSG875                    -2201750
#define XCSD_MSG876                    -2201752
#define XCSD_MSG877                    -2201754
#define XCSD_MSG878                    -2201756
#define XCSD_MSG879                    -2201758
#define XCSD_MSG880                    -2201760
#define XCSD_MSG881                    -2201762
#define XCSD_MSG882                    -2201764
#define XCSD_MSG883                    -2201766
#define XCSD_MSG884                    -2201768
#define XCSD_MSG885                    -2201770
#define XCSD_MSG886                    -2201772
#define XCSD_MSG887                    -2201774
#define XCSD_MSG888                    -2201776
#define XCSD_MSG889                    -2201778
#define XCSD_MSG890                    -2201780
#define XCSD_MSG891                    -2201782
#define XCSD_MSG892                    -2201784
#define XCSD_MSG893                    -2201786
#define XCSD_MSG894                    -2201788
#define XCSD_MSG895                    -2201790
#define XCSD_MSG896                    -2201792
#define XCSD_MSG897                    -2201794
#define XCSD_MSG898                    -2201796
#define XCSD_MSG899                    -2201798
#define XCSD_MSG900                    -2201800
#define XCSD_MSG901                    -2201802
#define XCSD_MSG902                    -2201804
#define XCSD_MSG903                    -2201806
#define XCSD_MSG904                    -2201808
#define XCSD_MSG905                    -2201810
#define XCSD_MSG906                    -2201812
#define XCSD_MSG907                    -2201814
#define XCSD_MSG908                    -2201816
#define XCSD_MSG909                    -2201818
#define XCSD_MSG910                    -2201820
#define XCSD_MSG911                    -2201822
#define XCSD_MSG912                    -2201824
#define XCSD_MSG913                    -2201826
#define XCSD_MSG914                    -2201828
#define XCSD_MSG915                    -2201830
#define XCSD_MSG916                    -2201832
#define XCSD_MSG917                    -2201834
#define XCSD_MSG918                    -2201836
#define XCSD_MSG919                    -2201838
#define XCSD_MSG920                    -2201840
#define XCSD_MSG921                    -2201842
#define XCSD_MSG922                    -2201844
#define XCSD_MSG923                    -2201846
#define XCSD_MSG924                    -2201848
#define XCSD_MSG925                    -2201850
#define XCSD_MSG926                    -2201852
#define XCSD_MSG927                    -2201854
#define XCSD_MSG928                    -2201856
#define XCSD_MSG929                    -2201858
#define XCSD_MSG930                    -2201860
#define XCSD_MSG931                    -2201862
#define XCSD_MSG932                    -2201864
#define XCSD_MSG933                    -2201866
#define XCSD_MSG934                    -2201868
#define XCSD_MSG935                    -2201870
#define XCSD_MSG936                    -2201872
#define XCSD_MSG937                    -2201874
#define XCSD_MSG938                    -2201876
#define XCSD_MSG939                    -2201878
#define XCSD_MSG940                    -2201880
#define XCSD_MSG941                    -2201882
#define XCSD_MSG942                    -2201884
#define XCSD_MSG943                    -2201886
#define XCSD_MSG944                    -2201888
#define XCSD_MSG945                    -2201890
#define XCSD_MSG946                    -2201892
#define XCSD_MSG947                    -2201894
#define XCSD_MSG948                    -2201896
#define XCSD_MSG949                    -2201898
#define XCSD_MSG950                    -2201900
#define XCSD_MSG951                    -2201902
#define XCSD_MSG952                    -2201904
#define XCSD_MSG953                    -2201906
#define XCSD_MSG954                    -2201908
#define XCSD_MSG955                    -2201910
#define XCSD_MSG956                    -2201912
#define XCSD_MSG957                    -2201914
#define XCSD_MSG958                    -2201916
#define XCSD_MSG959                    -2201918
#define XCSD_MSG960                    -2201920
#define XCSD_MSG961                    -2201922
#define XCSD_MSG962                    -2201924
#define XCSD_MSG963                    -2201926
#define XCSD_MSG964                    -2201928
#define XCSD_MSG965                    -2201930
#define XCSD_MSG966                    -2201932
#define XCSD_MSG967                    -2201934
#define XCSD_MSG968                    -2201936
#define XCSD_MSG969                    -2201938
#define XCSD_MSG970                    -2201940
#define XCSD_MSG971                    -2201942
#define XCSD_MSG972                    -2201944
#define XCSD_MSG973                    -2201946
#define XCSD_MSG974                    -2201948
#define XCSD_MSG975                    -2201950
#define XCSD_MSG976                    -2201952
#define XCSD_MSG977                    -2201954
#define XCSD_MSG978                    -2201956
#define XCSD_MSG979                    -2201958
#define XCSD_MSG980                    -2201960
#define XCSD_MSG981                    -2201962
#define XCSD_MSG982                    -2201964
#define XCSD_MSG983                    -2201966
#define XCSD_MSG984                    -2201968
#define XCSD_MSG985                    -2201970
#define XCSD_MSG986                    -2201972
#define XCSD_MSG987                    -2201974
#define XCSD_MSG988                    -2201976
#define XCSD_MSG989                    -2201978

/******************************************************************************
*end*of* xcsd_messages.h
*******************************************************************************/

#endif /* _XCSD_MESSAGES_H_ */


#ifndef _DE_MESSAGES_H_
#define _DE_MESSAGES_H_

/******************************************************************************
Module: de_messages.h

Message definitions generated 2020-10-21 15:24:39 by amt, version 3.19.7.0 - Built: 2017-12-30.

NOTE: Do not edit this file. It is automatically generated from
      one or more message files.
*******************************************************************************/

#define DE_DUPLICATE_TOKEN             -800002
#define DE_UNKNOWN_TOKEN               -800004
#define DE_INVALID_ORDERBOOK           -800006
#define DE_INVALID_SIDE                -800008
#define DE_INVALID_TIF                 -800010
#define DE_INVALID_ORDER_NUMBER        -800012
#define DE_CAN_NOT_CANCEL              -800014
#define DE_INVALID_TOKEN               -800016
#define DE_INVALID_OPEN_CLOSE          -800018
#define DE_INVALID_STPKEY              -800020

/******************************************************************************
*end*of* de_messages.h
*******************************************************************************/

#endif /* _DE_MESSAGES_H_ */


#ifndef _GEN_MESSAGES_H_
#define _GEN_MESSAGES_H_

/******************************************************************************
Module: gen_messages.h

Message definitions generated 2020-10-21 15:24:26 by amt, version 3.19.7.0 - Built: 2017-12-30.

NOTE: Do not edit this file. It is automatically generated from
      one or more message files.
*******************************************************************************/

#define GEN_CDC_OK                      110001
#define GEN_CDC_MEM_FULL               -110002
#define GEN_CDC_MEM_NOTFOU             -110003
#define GEN_CDC_TRC_NOTDEF             -110005
#define GEN_CDC_INS_NOTFOU             -110007
#define GEN_CDC_INT_NOTFOU             -110009
#define GEN_CDC_LIU_NOTFOU             -110011
#define GEN_CDC_LTT_NOTFOU             -110013
#define GEN_CDC_MAR_NOTFOU             -110015
#define GEN_CDC_USR_NOTFOU             -110017
#define GEN_CDC_CLI_NOTFOU             -110019
#define GEN_CDC_VPT_NOTFOU             -110021
#define GEN_CDC_INT_CLOSED             -110023
#define GEN_CDC_ILL_TRT_IN_USR         -110025
#define GEN_CDC_NO_MATCH               -110027
#define GEN_CDC_INT_FULL               -110028
#define GEN_CDC_INS_FULL               -110030
#define GEN_CDC_LTT_FULL               -110032
#define GEN_CDC_LIU_FULL               -110034
#define GEN_CDC_PQR_FULL               -110036
#define GEN_CDC_USR_FULL               -110038
#define GEN_CDC_MAR_FULL               -110040
#define GEN_CDC_RIT_FULL               -110042
#define GEN_CDC_VPT_FULL               -110044
#define GEN_CDC_CLI_FULL               -110046
#define GEN_CDC_INT_SIZE_FULL          -110048
#define GEN_CDC_USR_TRT_ID_FULL        -110050
#define GEN_CDC_NOT_INIT               -110051
#define GEN_CDC_NOT_LOCKED             -110053
#define GEN_CDC_NOT_UPDATER            -110055
#define GEN_CDC_LAST_TRADE             -110057
#define GEN_CDC_MAR_LOCKED             -110059
#define GEN_CDC_ILL_COMMODITY          -110061
#define GEN_CDC_CBS_FULL               -110062
#define GEN_CDC_VMS_FULL               -110064
#define GEN_CDC_ICO_FULL               -110066
#define GEN_CDC_USR_NAME_NOTFOU        -110068
#define GEN_CDC_NEAR_MAX_LIMIT         -110069
#define GEN_CDC_TABLE_NOT_FOUND        -110071
#define GEN_CDC_TRT_FULL               -110072
#define GEN_CDC_TRT_NOTFOU             -110073
#define GEN_CDC_PQR_NOTFOU             -110075
#define GEN_CDC_USR_SUSP               -110077
#define GEN_CDC_SYM_FULL               -110078
#define GEN_CDC_SYM_NOTFOU             -110079
#define GEN_CDC_CST_SUSP               -110081
#define GEN_CDC_VOL_FULL               -110082
#define GEN_CDC_NOT_VPT                -110083
#define GEN_CDC_NOT_VPD                -110085
#define GEN_CDC_VPD_FULL               -110086
#define GEN_CDC_VPD_NOTFOU             -110087
#define GEN_CDC_MKT_NOTVAL             -110089
#define GEN_CDC_BBO_NOTFOU             -110091
#define GEN_CDC_COM_NOTFOU             -110093
#define GEN_CDC_CRS_NOTFOU             -110095
#define GEN_CDC_INC_NOTFOU             -110097
#define GEN_CDC_SPR_NOTFOU             -110099
#define GEN_CDC_TRC_NOTFOU             -110101
#define GEN_CDC_BBO_FULL               -110102
#define GEN_CDC_COM_FULL               -110104
#define GEN_CDC_CRS_FULL               -110106
#define GEN_CDC_INC_FULL               -110108
#define GEN_CDC_SPR_FULL               -110110
#define GEN_CDC_TRC_FULL               -110112
#define GEN_CDC_OBL_FULL               -110114
#define GEN_CDC_OBL_NOTFOU             -110115
#define GEN_CDC_MSU_FULL               -110116
#define GEN_CDC_MSU_NOTFOU             -110117
#define GEN_CDC_COG_FULL               -110118
#define GEN_CDC_COG_NOTFOU             -110119
#define GEN_CDC_FML_FULL               -110120
#define GEN_CDC_FML_NOTFOU             -110121
#define GEN_CDC_OBK_FULL               -110122
#define GEN_CDC_OBK_NOTFOU             -110123
#define GEN_CDC_TSR_FULL               -110124
#define GEN_CDC_TSR_NOTFOU             -110125
#define GEN_CDC_EDG_FULL               -110126
#define GEN_CDC_EDG_NOTFOU             -110127
#define GEN_CDC_SPG_FULL               -110128
#define GEN_CDC_SPG_NOTFOU             -110129
#define GEN_CDC_PDP_FULL               -110130
#define GEN_CDC_PDP_NOTFOU             -110131
#define GEN_CDC_FOV_FULL               -110132
#define GEN_CDC_FOV_NOTFOU             -110133
#define GEN_CDC_TSE_FULL               -110134
#define GEN_CDC_TSE_NOTFOU             -110135
#define GEN_CDC_DES_FULL               -110136
#define GEN_CDC_DES_NOTFOU             -110137
#define GEN_CDC_EID_FULL               -110138
#define GEN_CDC_EID_NOTFOU             -110139
#define GEN_CDC_UST_FULL               -110140
#define GEN_CDC_UST_NOTFOU             -110141
#define GEN_CDC_EXC_FULL               -110142
#define GEN_CDC_EXC_NOTFOU             -110143
#define GEN_CDC_VDS_FULL               -110144
#define GEN_CDC_VDS_NOTFOU             -110145
#define GEN_CDC_DGR_FULL               -110146
#define GEN_CDC_DGR_NOTFOU             -110147
#define GEN_CDC_DHB_FULL               -110148
#define GEN_CDC_DHB_NOTFOU             -110149
#define GEN_CDC_SST_FULL               -110150
#define GEN_CDC_SST_NOTFOU             -110151
#define GEN_CDC_PRL_FULL               -110152
#define GEN_CDC_PRL_NOTFOU             -110153
#define GEN_CDC_SERIES_STOPPED         -110155
#define GEN_CDC_INV_BLOCK              -110157
#define GEN_CDC_INV_QUANTITY           -110159
#define GEN_CDC_INV_PREMIUM            -110161
#define GEN_CDC_INV_OPEN_CLOSE_REQ     -110163
#define GEN_CDC_CRSCLOSE               -110165
#define GEN_CDC_INVOPENCLOSE           -110167
#define GEN_CDC_MATCH_VALIDITY         -110169
#define GEN_CDC_INVUSER                -110171
#define GEN_CDC_MAX_QUANTITY           -110173
#define GEN_CDC_MIN_OF_SIL             -110175
#define GEN_CDC_MAR_CLOSED             -110177
#define GEN_CDC_BEFORE_TRD_TIME        -110179
#define GEN_CDC_AFTER_TRD_TIME         -110181
#define GEN_CDC_BEFORE_TX_TIME         -110183
#define GEN_CDC_AFTER_TX_TIME          -110185
#define GEN_CDC_CIB_FULL               -110186
#define GEN_CDC_CIB_NOTFOU             -110187
#define GEN_CDC_SID_FULL               -110188
#define GEN_CDC_SID_NOTFOU             -110189
#define GEN_CDC_NTD_FULL               -110190
#define GEN_CDC_NTD_NOTFOU             -110191
#define GEN_CDC_NO_HEDGE_PRICE         -110193
#define GEN_CDC_CRF_FULL               -110194
#define GEN_CDC_CRF_NOTFOU             -110195
#define GEN_CDC_CBX_FULL               -110196
#define GEN_CDC_CBX_NOTFOU             -110197
#define GEN_CDC_WKP_FULL               -110198
#define GEN_CDC_WKP_NOTFOU             -110199
#define GEN_CDC_MAX_MEM_QUANTITY       -110201
#define GEN_CDC_CRO_FULL               -110202
#define GEN_CDC_CRO_NOTFOU             -110203
#define GEN_CDC_CCR_FULL               -110204
#define GEN_CDC_CCR_NOTFOU             -110205
#define GEN_CDC_IXV_FULL               -110206
#define GEN_CDC_IXV_NOTFOU             -110207
#define GEN_CDC_VBS_FULL               -110208
#define GEN_CDC_AEX_FULL               -110210
#define GEN_CDC_AEX_NOTFOU             -110211
#define GEN_CDC_CSA_FULL               -110212
#define GEN_CDC_CSA_NOTFOU             -110213
#define GEN_CDC_SEC_FULL               -110214
#define GEN_CDC_SEC_NOTFOU             -110215
#define GEN_CDC_POD_FULL               -110216
#define GEN_CDC_POD_NOTFOU             -110217
#define GEN_CDC_CUP_FULL               -110218
#define GEN_CDC_CUP_NOTFOU             -110219
#define GEN_CDC_ING_FULL               -110220
#define GEN_CDC_ING_NOTFOU             -110221
#define GEN_CDC_EDL_FULL               -110222
#define GEN_CDC_EDL_NOTFOU             -110223
#define GEN_CDC_SPL_FULL               -110224
#define GEN_CDC_SPL_NOTFOU             -110225
#define GEN_CDC_VSP_FULL               -110226
#define GEN_CDC_VSP_NOTFOU             -110227
#define GEN_CDC_PRICE_NOTINLIM         -110229
#define GEN_CDC_SSS_FULL               -110230
#define GEN_CDC_SSS_NOTFOU             -110231
#define GEN_CDC_ECB_FULL               -110232
#define GEN_CDC_ECB_NOTFOU             -110233
#define GEN_CDC_CBS_NOT_READY          -110235
#define GEN_CDC_OAT_FULL               -110236
#define GEN_CDC_OAT_NOTFOU             -110237
#define GEN_CDC_PQC_FULL               -110238
#define GEN_CDC_PQC_NOTFOU             -110239
#define GEN_CDC_TRC_MEM_NOTFOUND       -110241
#define GEN_CDC_CPA_FULL               -110242
#define GEN_CDC_CPA_NOTFOU             -110243
#define GEN_CDC_ASC_FULL               -110244
#define GEN_CDC_ASC_NOTFOU             -110245
#define GEN_CDC_NOT_TRADED             -110247
#define GEN_CDC_BEFORE_FIRST           -110249
#define GEN_CDC_AFTER_LAST             -110251
#define GEN_CDC_PID_FULL               -110252
#define GEN_CDC_PID_NOTFOU             -110253
#define GEN_CDC_ONLY_IN_EQ_CBO         -110255
#define GEN_CDC_TRC_INS_NOTFOUND       -110257
#define GEN_CDC_TRC_SST_NOTFOUND       -110259
#define GEN_CDC_TRC_UST_NOTFOUND       -110261
#define GEN_CDC_CAC_FULL               -110262
#define GEN_CDC_CAC_NOTFOU             -110263
#define GEN_CDC_CUR_FULL               -110264
#define GEN_CDC_CUR_NOTFOU             -110265
#define GEN_CDC_OPP_FULL               -110266
#define GEN_CDC_OPP_NOTFOU             -110267
#define GEN_CDC_DIO_FULL               -110268
#define GEN_CDC_DIO_NOTFOU             -110269
#define GEN_CDC_RPT_FULL               -110270
#define GEN_CDC_RPT_NOTFOU             -110271
#define GEN_CDC_RTM_FULL               -110272
#define GEN_CDC_RTM_NOTFOU             -110273
#define GEN_CDC_CRP_FULL               -110274
#define GEN_CDC_CRP_NOTFOU             -110275
#define GEN_CDC_MPR_FULL               -110276
#define GEN_CDC_MPR_NOTFOU             -110277
#define GEN_CDC_MPM_FULL               -110278
#define GEN_CDC_MPM_NOTFOU             -110279
#define GEN_CDC_ONLY_TRADE_REPORTING   -110281
#define GEN_CDC_CSE_FULL               -110282
#define GEN_CDC_HSL_FULL               -110284
#define GEN_CDC_CSE_NOTFOU             -110285
#define GEN_CDC_HSE_FULL               -110286
#define GEN_CDC_HSE_NOTFOU             -110287
#define GEN_CDC_HSL_NOTFOU             -110289
#define GEN_LIST_NAME_NO_MARKET        -135000
#define GEN_LIST_NAME_NO_NAME          -135002
#define GEN_LIST_NAME_NO_TYPE          -135004
#define GEN_LIST_NAME_NOT_AST          -135006
#define GEN_LIST_NAME_TOO_SHORT        -135008
#define GEN_LIST_NAME_DUPL             -135010
#define GEN_LIST_NAME_DUPL_TYP         -135012
#define OC_BIND_FAIL                   -140000
#define OC_BRX_NOT_ALL                 -140001
#define OC_CALLCONN                     140003
#define OC_CLIENT_CONNECT               140005
#define OC_ERROR                       -140006
#define OC_FATAL                       -140008
#define OC_INFO                         140009
#define OC_INVARGS                     -140010
#define OC_INVCHN_TYPE                 -140012
#define OC_INVLEVEL                    -140014
#define OC_INVSRVNAM                   -140016
#define OC_MSG_XMT                      140017
#define OC_NO_EVENTS                    140019
#define OC_NORMAL                       140021
#define OC_PROTOCOLERR                 -140022
#define OC_READ_PRG                     140023
#define OC_SRV_ONLINE                   140025
#define OC_TX_ABORT_INPROG             -140026
#define OC_TX_ALLSRVSHA                -140028
#define OC_TX_ALLSRVSTA                -140030
#define OC_TX_ALRSHADOW                -140032
#define OC_TX_CH_ACTIVE                -140034
#define OC_TX_CH_NOTACTIVE             -140036
#define OC_TX_COMMIT                    140037
#define OC_TX_CONNOTSET                -140038
#define OC_TX_DATTYPDIF                -140040
#define OC_TX_DCLNOTTERM               -140041
#define OC_TX_DELAYTERM                 140043
#define OC_TX_EXINOTCON                -140044
#define OC_TX_INVACCESS                -140046
#define OC_TX_INVFACNAM                -140048
#define OC_TX_INVTXBUFLEN              -140050
#define OC_TX_KEYLENDIF                -140052
#define OC_TX_KEYOFFDIF                -140054
#define OC_TX_KEYOUTREC                -140056
#define OC_TX_KEYRANOVE                -140058
#define OC_TX_MSG_PEND                 -140060
#define OC_TX_NOACCESS                 -140062
#define OC_TX_NOACP                    -140064
#define OC_TX_NONDEQ_MSG                140065
#define OC_TX_NONTRM_READ              -140066
#define OC_TX_NONTRM_SRVCOM            -140067
#define OC_TX_NOSRV_FOR_KEY            -140068
#define OC_TX_NOT_OPEN                 -140070
#define OC_TX_NOTACTIVE                -140072
#define OC_TX_NOTSAMCLU                -140074
#define OC_TX_NOTSAMNOD                -140076
#define OC_TX_NRSEGSDIF                -140078
#define OC_TX_OUTST_EVTSDWN            -140080
#define OC_TX_REQABORT                 -140082
#define OC_TX_REQCALLUN                -140084
#define OC_TX_SHUTCALL                 -140085
#define OC_TX_SHUTDOWN                 -140087
#define OC_TX_START                     140089
#define OC_TX_STARTREC                  140091
#define OC_TX_TOOMANSHA                -140092
#define OC_TX_TRUNCATE                 -140094
#define OC_TX_TWONODALR                -140096
#define OC_TX_UPPLESLOW                -140098
#define OC_TX_VOTE                      140099
#define OC_TRNS_UNSUPP                 -140100
#define OC_TX_JOUOVERFL                -140102
#define OC_TX_JOUFILFUL                -140104
#define OC_TX_JOUFILERR                -140106
#define GEN_TRADE_NOSUBS                175001
#define GEN_SHR_DVPCOMPLETEDNOCANCEL   -197000
#define GEN_SHR_DVPRECALLEDNOCANCEL    -197002
#define GEN_SHR_DVPCANCELLEDNOCANCEL   -197004
#define GEN_SHR_NEEDSAUTHORIZATION      197005
#define GEN_SHR_INVFIXEDINCOMETYPE     -197006
#define GEN_SHR_ILLEGALARGUMENT        -197008
#define GEN_SHR_INVPREMIUMUNIT         -197010
#define GEN_SHR_FIXEDINCOMEPRODUCT     -197012
#define GEN_SHR_FIXEDINCOMEPRICETYPE   -197014
#define GEN_SHR_INVSERIES              -197016
#define GEN_SHR_NOTTMTEMPLATE          -197018
#define GEN_SHR_NOTTMSERIES            -197020
#define GEN_SHR_INTERROR               -197022
#define GEN_SHR_SERIESMISMATCH         -197024
#define GEN_SHR_INVINSID               -197026
#define GEN_SHR_NEEDSFURTHERAUTH        197027
#define GEN_MDF_VERSION                 199001

/******************************************************************************
*end*of* gen_messages.h
*******************************************************************************/

#endif /* _GEN_MESSAGES_H_ */


#ifndef _IN_MESSAGES_H_
#define _IN_MESSAGES_H_

/******************************************************************************
Module: in_messages.h

Message definitions generated 2020-10-21 15:24:27 by amt, version 3.19.7.0 - Built: 2017-12-30.

NOTE: Do not edit this file. It is automatically generated from
      one or more message files.
*******************************************************************************/

#define IDL_BSSDATANOTFOU              -505000
#define IDL_BSSNOTFOU                  -505002
#define IDL_BSSTABFULL                 -505004
#define IDL_COMDATANOTFOU              -505006
#define IDL_COMNOTFOU                  -505008
#define IDL_COMTABFULL                 -505010
#define IDL_EXCDATANOTFOU              -505012
#define IDL_EXCNOTFOU                  -505014
#define IDL_EXCTABFULL                 -505016
#define IDL_INCDATANOTFOU              -505018
#define IDL_INCNOTFOU                  -505020
#define IDL_INCTABFULL                 -505022
#define IDL_INSDATANOTFOU              -505024
#define IDL_INSNOTFOU                  -505026
#define IDL_INSTABFULL                 -505028
#define IDL_INTDATANOTFOU              -505030
#define IDL_INTNOTFOU                  -505032
#define IDL_INTTABFULL                 -505034
#define IDL_MARDATANOTFOU              -505036
#define IDL_MARNOTFOU                  -505038
#define IDL_MARTABFULL                 -505040
#define IDL_SYMDATANOTFOU              -505042
#define IDL_SYMNOTFOU                  -505044
#define IDL_SYMTABFULL                 -505046
#define IDL_TSSDATANOTFOU              -505048
#define IDL_TSSNOTFOU                  -505050
#define IDL_TSSTABFULL                 -505052
#define IDL_VMSDATANOTFOU              -505054
#define IDL_VMSNOTFOU                  -505056
#define IDL_VMSTABFULL                 -505058
#define IDL_VOLDATANOTFOU              -505060
#define IDL_VOLNOTFOU                  -505062
#define IDL_VOLTABFULL                 -505064
#define IDL_BBODATANOTFOU              -505066
#define IDL_BBONOTFOU                  -505068
#define IDL_BBOTABFULL                 -505070
#define IDL_TRCDATANOTFOU              -505072
#define IDL_TRCNOTFOU                  -505074
#define IDL_TRCTABFULL                 -505076
#define IDL_OBKDATANOTFOU              -505078
#define IDL_OBKNOTFOU                  -505080
#define IDL_OBKTABFULL                 -505082
#define IDL_AEXDATANOTFOU              -505084
#define IDL_AEXNOTFOU                  -505086
#define IDL_AEXTABFULL                 -505088
#define IDL_TSEDATANOTFOU              -505090
#define IDL_TSENOTFOU                  -505092
#define IDL_TSETABFULL                 -505094
#define IDL_SSTDATANOTFOU              -505096
#define IDL_SSTNOTFOU                  -505098
#define IDL_SSTTABFULL                 -505100
#define IDL_PTDDATANOTFOU              -505102
#define IDL_PTDNOTFOU                  -505104
#define IDL_PTDTABFULL                 -505106
#define IDL_IPRDATANOTFOU              -505108
#define IDL_IPRNOTFOU                  -505110
#define IDL_IPRTABFULL                 -505112
#define IDL_EIDDATANOTFOU              -505114
#define IDL_EIDNOTFOU                  -505116
#define IDL_EIDTABFULL                 -505118
#define IDL_DHBDATANOTFOU              -505120
#define IDL_DHBNOTFOU                  -505122
#define IDL_DHBTABFULL                 -505124
#define IDL_DESDATANOTFOU              -505126
#define IDL_DESNOTFOU                  -505128
#define IDL_DESTABFULL                 -505130
#define IDL_DGRDATANOTFOU              -505132
#define IDL_DGRNOTFOU                  -505134
#define IDL_DGRTABFULL                 -505136
#define IDL_VDSDATANOTFOU              -505138
#define IDL_VDSNOTFOU                  -505140
#define IDL_VDSTABFULL                 -505142
#define IDL_MEMDATANOTFOU              -505144
#define IDL_MEMNOTFOU                  -505146
#define IDL_MEMTABFULL                 -505148
#define IDL_CBXDATANOTFOU              -505150
#define IDL_CBXNOTFOU                  -505152
#define IDL_CBXTABFULL                 -505154
#define IDL_PSPDATANOTFOU              -505156
#define IDL_PSPNOTFOU                  -505158
#define IDL_PSPTABFULL                 -505160
#define IDL_USRDATANOTFOU              -505162
#define IDL_USRNOTFOU                  -505164
#define IDL_USRTABFULL                 -505166
#define IDL_CBSDATANOTFOU              -505168
#define IDL_CBSNOTFOU                  -505170
#define IDL_CBSTABFULL                 -505172
#define IDL_SBSDATANOTFOU              -505174
#define IDL_SBSNOTFOU                  -505176
#define IDL_SBSTABFULL                 -505178
#define IDL_CORRUPTED                  -505180
#define IDL_CONSISTENT                  505181
#define IDL_WRONGLCK                   -505182
#define IDL_CCRDATANOTFOU              -505184
#define IDL_CCRNOTFOU                  -505186
#define IDL_CCRTABFULL                 -505188
#define IDL_IXVDATANOTFOU              -505190
#define IDL_IXVNOTFOU                  -505192
#define IDL_IXVTABFULL                 -505194
#define IDL_CUPDATANOTFOU              -505196
#define IDL_CUPNOTFOU                  -505198
#define IDL_CUPTABFULL                 -505200
#define IDL_INGDATANOTFOU              -505202
#define IDL_INGNOTFOU                  -505204
#define IDL_INGTABFULL                 -505206
#define IDL_NTDDATANOTFOU              -505208
#define IDL_NTDNOTFOU                  -505210
#define IDL_NTDTABFULL                 -505212
#define IDL_CIBDATANOTFOU              -505214
#define IDL_CIBNOTFOU                  -505216
#define IDL_CIBTABFULL                 -505218
#define IDL_COGDATANOTFOU              -505220
#define IDL_COGNOTFOU                  -505222
#define IDL_COGTABFULL                 -505224
#define IDL_DSCDATANOTFOU              -505226
#define IDL_DSCNOTFOU                  -505228
#define IDL_DSCTABFULL                 -505230
#define IDL_CURNOTFOU                  -505232
#define IDL_CURDATANOTFOU              -505234
#define IDL_CURTABFULL                 -505236
#define IDL_LITNOTFOU                  -505238
#define IDL_LITDATANOTFOU              -505240
#define IDL_LITTABFULL                 -505242
#define IDL_ISSDATANOTFOU              -505244
#define IDL_ISSNOTFOU                  -505246
#define IDL_ISSTABFULL                 -505248
#define IDL_TRTDATANOTFOU              -505250
#define IDL_TRTNOTFOU                  -505252
#define IDL_TRTTABFULL                 -505254
#define IDL_LTUDATANOTFOU              -505256
#define IDL_LTUNOTFOU                  -505258
#define IDL_LTUTABFULL                 -505260
#define IDL_SSSDATANOTFOU              -505262
#define IDL_SSSNOTFOU                  -505264
#define IDL_SSSTABFULL                 -505266
#define IDL_OATDATANOTFOU              -505268
#define IDL_OATNOTFOU                  -505270
#define IDL_OATTABFULL                 -505272
#define IDL_SCRDATANOTFOU              -505274
#define IDL_SCRNOTFOU                  -505276
#define IDL_SCRTABFULL                 -505278
#define IDL_PRLDATANOTFOU              -505280
#define IDL_PRLNOTFOU                  -505282
#define IDL_PRLTABFULL                 -505284
#define IDL_RPSDATANOTFOU              -505286
#define IDL_RPSNOTFOU                  -505288
#define IDL_RPSTABFULL                 -505290
#define INFO_OPERATORLOG               -510000
#define INFO_RESTART_OPERATION          510001
#define INFO_SXBUFFUL                  -510002
#define INFO_SXCSUMERR                 -510004
#define INFO_SXINVEXCCODE              -510006
#define INFO_SXMSGLENERR               -510008
#define INFO_SXMSGUNK                  -510010
#define INFO_SXNOOMX                   -510012
#define INFO_SXRTRYEXH                 -510014
#define INFO_BADTRDSYNCH               -510016
#define INFO_NOTRDSYNCH                -510018
#define INFO_BADORDSYNCH               -510020
#define INFO_INITNOTPASSED             -510022
#define INFO_PRIMTOSOON                -510024
#define INFO_NOTONETOONEMP             -510026
#define INFO_PANIC                     -510028
#define INFO_SERIESNOTFOU              -510030
#define INFO_PRIMARY                    510031
#define INFO_WAITPRIM                   510033
#define INFO_PRIMFOUND                  510035
#define INFO_MODDEPTH                   510037
#define INFO_NOMODDEPTH                 510039
#define INFO_NEWDEAL                    510041
#define INFO_NEWTRADE                   510043
#define INFO_DELDEAL                    510045
#define INFO_SKIPDEAL                   510047
#define INFO_SKIPORDER                  510049
#define INFO_TRDSYNCH                   510051
#define INFO_ORDSYNCH                   510053
#define INFO_DEALNOTFOU                -510055
#define INFO_DUPDEAL                   -510057
#define INFO_DUPORDER                  -510059
#define INFO_ORDERNOTFOU               -510061
#define INFO_SPREADUNSAFE              -510063
#define INFO_INDEXDUNSAFE              -510065
#define INFO_OK                         510067
#define INFO_NYI                        510069
#define INFO_BUGCHECK                  -510070
#define INFO_INSFMEM                   -510072
#define INFO_ABORT                     -510074
#define INFO_SUCCESS                    510075
#define INFO_NOINFO                    -510077
#define INFO_TODAYNOTAVAIL             -510079
#define INFO_BADSEG                    -510080
#define INFO_INVDATEFORM               -510082
#define INFO_INVFROMTODATE             -510084
#define INFO_NOTINMEMDB                 510085
#define INFO_NOINFOUV                  -510087
#define INFO_NOINFOINS                 -510089
#define INFO_NODEFSERVICES             -510091
#define INFO_MARGINQUOTESUPD           -510093
#define INFO_MARGINQUOTESVIEWED        -510095
#define INFO_IVBUFLEN                  -510096
#define INFO_FILENOTFOUND              -510098
#define INFO_NO_DATA_RETRY             -510099
#define INFO_FORCEDROLL                -510100
#define INFO_DB_RETRY_EXHAUSTED        -510102
#define INFO_TRAVERSEND                -510104
#define INFO_RTRERROR                  -510106
#define INFO_PRIMGROUPSHUT             -510108
#define INFO_COMPLETE                   510109
#define INFO_SSLNOCLOSE                -510111
#define INFO_SSLWVERISON               -510112
#define INFO_SSLNOLOGFILE              -510113
#define INFO_SSLNOTLOGENA              -510115
#define INFO_SSLNOMOUNT                -510116
#define INFO_SSLNOCHANNEL              -510117
#define INFO_SSLCALLBCKREG             -510118
#define INFO_SSLRICNOTOPEN             -510119
#define INFO_SSLNODISPATCH             -510120
#define INFO_SSLDISCONNECT             -510122
#define INFO_SSLRECONNECT               510123
#define INFO_SSLRICICLOSED              510125
#define INFO_SSLRICINFO                 510127
#define INFO_SSLRICOK                   510129
#define INFO_SSLRICSTALE               -510131
#define INFO_SSLEVUNK                   510133
#define INFO_SSLDISMOUNT               -510135
#define INFO_SSLNOWALIDD               -510136
#define INFO_NOTAWAYMARKET             -510138
#define INFO_NOSERIESTERM               510139
#define INFO_OPERNOTACC                -510140
#define INFO_OPERNYI                   -510142
#define INFO_UNKNOWNOPER               -510144
#define INFO_NEWFIRSTDEAL               510145
#define INFO_DELFIRSTDEAL               510147
#define INFO_DELLASTDEAL                510149
#define INFO_NOTALLOCATED              -510150
#define INFO_NOHOLDBACK                 510151
#define INFO_RETRANSNOTHAND            -510153
#define INFO_ONEINVUNDERLYING          -510155
#define INFO_MODULENOTINIT             -510156
#define INFO_PTDNOTUNIQUE              -510157
#define INFO_INCNOTFOUND               -510159
#define INFO_NOREFTOTIMER              -510161
#define INFO_MODBEST                    510163
#define INFO_CINTNOTFOU                 510165
#define INFO_INSNOTFOU                  510167
#define INFO_BO31NOTADDED               510169
#define INFO_BO35NOTADDED               510171
#define INFO_BD2NOTADDED                510173
#define INFO_MISSINGTIMERREF            510175
#define INFO_HBINTTOSHORT               510177
#define INFO_IPRNOTFOU                 -510178
#define INFO_BO3XNOTADDED               510179
#define INFO_INSNOTADDED                510181
#define INFO_CINTNOTADDED               510183
#define INFO_NOHDLYIELDDIFF            -510184
#define INFO_FUNCNOTSUP                -510186
#define INFO_HBBDCLATE                 -510188
#define INFO_ABORTSTATEREADY           -510190
#define INFO_ABORTNOMATCH              -510192
#define INFO_DATALCKBYSIGNAL           -510194
#define INFO_NOVALUNDERLYING           -510195
#define INFO_ONEINSNOOFFPRICE          -510196
#define INFO_ILLORDERTYPE               510197
#define INFO_PATCHNODEALS              -510198
#define INFO_PATCHDEALGONE             -510200
#define INFO_PATCHVOLERROR             -510202
#define INFO_DUALOPRALINEUSE            510203
#define INFO_TSISCOMBO                  510205
#define INFO_COLFAILNOSOURCE           -510206
#define INFO_NOITEMS                   -510208
#define INFO_INVALIDPRICESOURCE        -510210
#define INFO_MISSINGGROUP              -510212
#define INFO_DIRTYFUTURE               -510214
#define INFO_DIRTYWI                   -510216
#define INFO_DIRTYMONEY                -510218
#define INFO_INDICATIVEPRICETYPE       -510220
#define INFO_INVALIDPRICETYPE          -510222
#define INFO_CALCRULENOTAPLUND         -510224
#define INFO_NOTFOU                    -510226
#define INFO_ABORTSTATEUNDO            -510228
#define INFO_INVSUBITEMHDRSIZE         -510230
#define INFO_INVSUBITEMHDR             -510232
#define INFO_SUBITEMDROPPED            -510234
#define INFO_INVNAMEDSTRUCT            -510236
#define INFO_INVVITSIZE                -510238
#define INFO_INVVIQSIZE                -510240
#define INFO_INVVITITEMS               -510242
#define INFO_INVVIQITEMS               -510244
#define INFO_INVSUBITEMCOM             -510246
#define INFO_INVSUBITEMSTATUS          -510248
#define INFO_NOVALSUBITEMS             -510250
#define INFO_ONEINVSUBITEM             -510252
#define INFO_ONOFFOUTRANGE             -510254
#define INFO_WRNGEXTPRV                -510255
#define INFO_INVPRICE                  -510256
#define INFO_INVVOLUME                 -510258
#define INFO_INVMESSAGE                -510260
#define INFO_NOTISSUER                 -510262
#define INFO_INTSYN                    -510264
#define INFO_INTSEM                    -510266
#define INFO_BDCSYN                    -510268
#define INFO_BDCSEM                    -510270
#define INFO_ERRORCODE                 -510272
#define INFO_INVINSTRUMENT             -510274
#define INFO_INVSETTLETYPE             -510276
#define INFO_INVDEALSOURCE             -510278
#define INFO_INSNOTALLOWED             -510280
#define INFO_NOTRDYTRYLATER            -510282
#define INFO_HISDATENOTALWD            -510284
#define INFO_INVCRULEUSEWCALC          -510286
#define INFO_INVTIMEFORM               -510288
#define INFO_INVAONFIELD               -510290
#define INFO_INVTRENDIND               -510292
#define INFO_INVOPTRDHOLIDAY           -510294
#define INFO_TOMANYAGVLEVELS           -510296
#define INFO_AGVLEVELDROPPED           -510298
#define INFO_INDEXVALIDFAIL            -510300
#define INFO_INVINDEXOPER              -510302
#define INFO_RESETIXHILOFAIL           -510304
#define INFO_INVACCEXCHRATE            -510306
#define INFO_TXKEEPALIVE                510307
#define INFO_INDEXCALCFAIL             -510308
#define INFO_INDEXJOURNALFAIL          -510310
#define INFO_INDEXINDICESLOGFAIL       -510312
#define INFO_NOTSUPEAS                 -510314
#define INFO_ONEFMPUNDERLYING          -510316
#define INFO_STRTRUNCATED              -510317
#define INFO_SLAEXCEEDED               -510319
#define INFO_SPINVFORTHEOALG           -510320
#define INFO_SPINVFORALG               -510322
#define INFO_SPTOMANYMATCHES           -510324
#define INFO_SPINVALGO                 -510326
#define INFO_SPINVALGOFORPROD          -510328
#define INFO_SPINVASLOCKED             -510330
#define INFO_SPGENERICERROR            -510332
#define INFO_SPINVMANUALLYFLAG         -510334
#define INFO_SPMIXFUTOPT               -510336
#define INFO_SPNOTALLOPT               -510338
#define INFO_SPINVCLEARINGDATE         -510340
#define INFO_SPRULEOUTOFRANGE          -510342
#define INFO_SPOPTEXPANDMAXLIMIT       -510344
#define INFO_NOTAUTHORIZEDINS          -510345
#define INFO_BO6SEQNBRDROP              510347
#define INFO_SQLERROR                  -510348
#define INFO_OBPOSITIONERROR           -510350
#define INFO_BLACKLISTED               -510352
#define INFO_INVREFPRICETYPE           -510354
#define INFO_DD_RETRY_EXHAUSTED        -510356
#define PMI_GENRSPABN                  -515000
#define PMI_MALLOCERR                  -515002
#define PMI_LISTRSPABN                 -515004
#define PMI_INITRSPABN                 -515006
#define PMI_NOFREEBLOCK                -515008
#define PMI_NOINCFOUND                 -515010
#define PMI_NOINSFOUND                 -515012
#define PMI_NOUNDFOUND                 -515014
#define PMI_PMISTSABN                  -515015
#define PMI_QANSWOVERFLOW              -515016
#define INREU_INVMSGFMT                -520000
#define INREU_JOKE                     -520002
#define INREU_CFGCMDLNG                -520004
#define INREU_NOCFGFIL                 -520006
#define INREU_NOCRSREF                 -520008
#define INREU_NORICDEF                 -520010
#define INREU_NOPARENTDE               -520012
#define INREU_NOCOMCODDEF              -520014
#define INREU_INVBSTDEF                -520016
#define INREU_ONEBSTDEF                -520018
#define INREU_OMXRECDEF                -520020
#define INREU_NOOMXREC                 -520022
#define INREU_OMXNOTDEF                -520024
#define INREU_OMXNOFLD                 -520026
#define INREU_OMXDEF                   -520028
#define INREU_OMXONEFLD                -520030
#define INREU_OMXOVRLAP                -520032
#define INREU_OMXDBLFLDNO              -520034
#define INREU_INVBDXTYP                -520036
#define INREU_CONNFAIL                 -520038
#define INREU_DCLRCF                   -520040
#define INREU_DCLRTF                   -520042
#define INREU_ISINLEN                  -520044
#define INREU_INVSTSMSG                -520046
#define INREU_ASYINTERR                -520048
#define INREU_ASYDEVACT                -520050
#define INREU_ASYNOVLDCNTX             -520052
#define INREU_ASYNOSTOP                -520054
#define INREU_INVEXPFLD                -520056
#define INREU_INVINSTTYPFLD            -520058
#define INREU_INVTIMFLD                -520060
#define INREU_INVDATFLD                -520062
#define INREU_INVRECSIZ                -520064
#define INREU_BDXNOTDEF                -520066
#define INREU_REUSTS                   -520068
#define INREU_REUPROTERR               -520070
#define INREU_INVCRF                   -520072
#define INREU_NOSERIEDEF               -520074
#define INREU_NOINDEXDEF               -520076
#define INREU_NORMAL                    520077
#define INREU_WRNGSEQNBR               -520079
#define OPRA_CACH_INS_FULL             -525000
#define OPRA_CACH_CINT_FULL            -525002
#define OPRA_CACH_GRP_FULL             -525004
#define OPRA_CACH_EXC_FULL             -525006
#define OPRA_CACH_INS_NOT_RDY          -525008
#define OPRA_CACH_CINT_NOT_RDY         -525010
#define OPRA_CACH_GROUP_NOT_RDY        -525012
#define OPRA_CACH_EXC_NOT_RDY          -525014
#define OPRA_CACH_INSNOTFOU            -525016
#define IN_CQATS_FILEOPRFAILED         -530001
#define IN_CQATS_NORMAL                 530003
#define IN_CQATS_FEED_UNRELIABLE       -530004
#define IN_CQATS_NEW_UNKNOWN_MESSAGE    530005
#define IN_CQATS_UNEXP_SEQUENCE_NUMBER -530007
#define IN_CQATS_CORRECTION_FAILURE    -530009
#define IN_CQATS_CANCEL_FAILURE        -530011
#define IN_ULFEED_FILEOPRFAILED        -535001
#define IN_ULFEED_NORMAL                535003
#define IN_ULFEED_FEED_UNRELIABLE      -535004
#define IN_ULFEED_NEW_UNK_MESSAGE       535005
#define IN_ULFEED_UNEXP_SEQ_NUMBER     -535007
#define IN_ULFEED_CORRECTION_FAILURE   -535009
#define IN_ULFEED_CANCEL_FAILURE       -535011
#define IN_ULFEED_COMNOTFND             535013
#define IN_MDF_VERSION                  540001

/******************************************************************************
*end*of* in_messages.h
*******************************************************************************/

#endif /* _IN_MESSAGES_H_ */


#ifndef _LM_MESSAGES_H_
#define _LM_MESSAGES_H_

/******************************************************************************
Module: lm_messages.h

Message definitions generated 2020-10-21 15:24:27 by amt, version 3.19.7.0 - Built: 2017-12-30.

NOTE: Do not edit this file. It is automatically generated from
      one or more message files.
*******************************************************************************/

#define LM_PANIC                       -600000
#define LM_SUCCESS                      600001
#define LM_NORMAL                       600003
#define LM_INFORMATION                  600005
#define LM_INVTRANSSIZE                -600006
#define LM_INVTRANSTYPE                -600008
#define LM_INTERNALERROR               -600009
#define LM_INVTX                       -600011
#define LM_INVSEGMENTNR                -600013
#define LM_INSFMEM                     -600014
#define LM_BUGCHECK                    -600016
#define LM_ABORT                       -600018
#define LM_SUP_EXINSID_HASH            -600020
#define LM_SUP_INSID_FULL              -600022
#define LM_SUP_INV_INSID_KEY           -600024
#define LM_SUP_INV_LST_KEY             -600026
#define LM_SUP_INV_MM_KEY              -600028
#define LM_SUP_ORDERTYPE               -600030
#define LM_SUP_INV_PQR_KEY             -600032
#define LM_SUP_INV_PRM_KEY             -600034
#define LM_SUP_LST_FULL                -600036
#define LM_SUP_MM_FULL                 -600038
#define LM_SUP_NOT_OPEN                -600040
#define LM_SUP_PQR_FULL                -600042
#define LM_SUP_PRM_FULL                -600044
#define LM_SUP_SPREAD_NOTFND           -600046
#define LM_SUP_COMM_NOTFND             -600047
#define LM_SUP_INSID_NOTFND            -600049
#define LM_SUP_NO_INSID                -600051
#define LM_SUP_NO_LST_ID               -600053
#define LM_SUP_NOT_INIT                -600055
#define LM_SUP_NOT_LOCKED              -600057
#define LM_SUP_PQR_NOTFND              -600059
#define LM_SUP_PQR_ALTERED              600061
#define LM_SUP_LST_ALTERED              600063
#define LM_SUP_VOL_ALTERED              600065
#define LM_SUP_NOT_UPDATER             -600067
#define LM_SUP_END_OF_LIST             -600069
#define LM_SUP_NO_RESP_MM              -600071
#define LM_SUP_NO_VOL_ID               -600073
#define LM_SUP_MM_NOTRESP              -600075
#define LM_SUP_OLD_INSID               -600077
#define LM_SUP_BID_PRI_MISS            -600079
#define LM_SUP_ASK_PRI_MISS            -600081
#define LM_SUP_BOTH_PRI_MISS           -600083
#define LM_SUP_BID_QTY_INV             -600085
#define LM_SUP_ASK_QTY_INV             -600087
#define LM_SUP_BOTH_QTY_INV            -600089
#define LM_SUP_INV_SPREAD              -600091
#define LM_SUP_INV_VOL_SPR             -600093
#define LM_SUP_OLD_ORDER               -600095
#define LM_SUP_PRM_NOTFND              -600097
#define LM_SUP_INV_VOL_KEY             -600098
#define LM_SUP_VOL_FULL                -600100
#define LM_SUP_VSPREAD_NOTFND          -600102
#define LM_SUP_INV_MEMBER              -600104
#define LM_SUP_INV_VOTE                -600106
#define LM_SUP_INV_ORDERTYPE           -600108
#define LM_MMSUP_RELOAD_OB              600109
#define LM_MMSUP_NOT_INIT              -600111
#define LM_MMSUP_INVLEN                -600112
#define LM_MMSUP_INVTXTYP              -600114
#define LM_MMSUP_BAD_FORMAT            -600115
#define LM_MMSUP_INV_BOOLEAN           -600117
#define LM_MMSUP_INV_PARAM             -600119
#define LM_MMSUP_INV_TIME              -600121
#define LM_MMSUP_NO_PRICES             -600123
#define LM_MMSUP_NOT_LEGITIMATE        -600125
#define LM_MMSUP_MAR_CLOSED            -600127
#define LM_MMSUP_COMM_STOP             -600129
#define LM_MMSUP_INV_ORDERTYPE         -600131
#define LM_MMSUP_INV_BLOCK             -600133
#define LM_MMSUP_ILL_TRT_IN_USR        -600135
#define LM_MMSUP_TOO_MANY              -600137
#define LM_MMSUP_NONE_FOUND            -600139
#define LM_MMSUP_NOT_USER              -600140
#define LM_LSSRV_MARKET_HOURS          -600142
#define LM_CROSS_REQ_OK                 600143
#define LM_CROSS_REQ_OK_2              -600144
#define LM_CROSS_REQ_ENDED              600145
#define LM_CROSS_BLOCK_RELEASED         600147
#define LM_CROSS_MAR_ESTAB              600149
#define LM_CROSS_MAR_TIMOUT             600151
#define LM_CROSS_REQ_MEM_ACT           -600152
#define LM_CROSS_REQ_BLOCKED           -600154
#define LM_CROSS_INSID_NOTFND          -600156
#define LM_CROSS_NOT_USER              -600158
#define LM_CROSS_REQ_NOT_FOUND         -600160
#define LM_CROSS_INT_NOT_ALLOWED       -600162
#define LM_FILENOTFOUND                -600164
#define LM_INV_ALARM_TYPE              -600165
#define LM_INV_ALARM_STATUS            -600167
#define LM_MM_NOT_FOUND                -600169
#define LM_MMSUP_LAST_PRI_MISSING      -600171
#define LM_MMSUP_INS_DELISTED          -600173
#define LM_MMSUP_NOT_TRADED            -600175
#define LM_SUP_COM_ALTERED              600177
#define LM_SUP_COM_FULL                -600178
#define LM_SUP_ILL_QTY                 -600180
#define LM_MMSUP_REP_CRE_FAILED        -600182
#define LM_MMSUP_LOGP_VERSION          -600184
#define LM_LSSRV_INFO_TYPE             -600186
#define LM_SUP_ILL_BLK_SIZE            -600188
#define LM_MMS_RELOAD_OB                600189
#define LM_MMS_NOT_INIT                -600191
#define LM_MMS_INVLEN                  -600192
#define LM_MMS_INVTXTYP                -600194
#define LM_MMS_BAD_FORMAT              -600195
#define LM_MMS_INV_BOOLEAN             -600197
#define LM_MMS_INV_PARAM               -600199
#define LM_MMS_INV_TIME                -600201
#define LM_MMS_NO_PRICES               -600203
#define LM_MMS_NOT_LEGITIMATE          -600205
#define LM_MMS_MAR_CLOSED              -600207
#define LM_MMS_COMM_STOP               -600209
#define LM_MMS_INV_ORDERTYPE           -600211
#define LM_MMS_INV_BLOCK               -600213
#define LM_MMS_ILL_TRT_IN_USR          -600215
#define LM_MMS_TOO_MANY                -600217
#define LM_MMS_NONE_FOUND              -600219
#define LM_MMS_NOT_USER                -600220
#define LM_MMS_LAST_PRI_MISSING        -600221
#define LM_MMS_INS_DELISTED            -600223
#define LM_MMS_NOT_TRADED              -600225
#define LM_MMS_REP_CRE_FAILED          -600226
#define LM_MMS_LOGP_VERSION            -600228
#define LM_BADPARAM                    -600230
#define LM_DUPLNAM                     -600232
#define LM_BADFILEHDR                  -600234
#define LM_SERIES_NOTFOUND             -600236
#define LM_NORMAL_EOF                   600237
#define LM_MISSING_ENV_VAR             -600238
#define LM_TRS_ALARM_FOPEN             -600240
#define LM_SUP_BID_PRI_MIS_ASK_QTY_INV -600241
#define LM_SUP_ASK_PRI_MIS_BID_QTY_INV -600243
#define LM_SUP_INV_SPREAD_BOTH_QTY_INV -600245
#define LM_SUP_INV_SPREAD_ASK_QTY_INV  -600247
#define LM_SUP_INV_SPREAD_BID_QTY_INV  -600249
#define LM_MDF_VERSION                  605001
#define LM_NRS_FILE_NOT_FOUND          -610000
#define LM_NRS_FILE_LOCKED             -610002
#define LM_NRS_REC_CRS_BOUND           -610004
#define LM_NRS_INV_REC_FORMAT          -610006
#define LM_NRS_RIGHTS_NOT_FOUND        -610008

/******************************************************************************
*end*of* lm_messages.h
*******************************************************************************/

#endif /* _LM_MESSAGES_H_ */


#ifndef _MP_MESSAGES_H_
#define _MP_MESSAGES_H_

/******************************************************************************
Module: mp_messages.h

Message definitions generated 2020-10-21 15:24:27 by amt, version 3.19.7.0 - Built: 2017-12-30.

NOTE: Do not edit this file. It is automatically generated from
      one or more message files.
*******************************************************************************/

#define MP_MDF_VERSION                  401001
#define MP_COUNTERS_NOT_INIT           -405000
#define MP_INFORMATION                  405001
#define MP_SUCCESS                      405003
#define MP_PANIC                       -405004
#define MP_INSFMEM                     -405006
#define MP_BUGCHECK                    -405007
#define MP_QUOTA                       -405009
#define MP_IVBUFLEN                    -405010
#define MP_ABORT                       -405012
#define MP_COMMIT_LOG_UNKNOWN          -405014
#define MP_INVINT                      -405016
#define MP_NOHIT                       -405017
#define MP_LISEMPTY                    -405019
#define MP_OVERFLOW                    -405021
#define MP_RECEXCLEN                   -405022
#define MP_WRNGFTYP                    -405024
#define MP_OPLOG_FULL                  -405026
#define MP_FILE_NOT_FOUND              -405028
#define MP_NOT_ALLW_WKUP_STATE         -405029
#define MP_NOT_EXP_RESULT              -405031
#define MP_INV_USR                     -405033
#define MP_FILE_LOCKED                 -405035
#define MP_EOF                          405037
#define MP_BUFFER_SMALL                -405039
#define MP_QUEUE_ALMOST_FULL            405041
#define MP_NO_PQR_IN_UND               -405042
#define MP_MARKET_MAKER_PROTECTION     -405044
#define MP_MARKET_MAKER_PROTECTION_SET  405045
#define MP_MARKET_MAKER_TRADE           405047
#define MP_MM_VOLUME_PROTECTION        -405048
#define MP_MM_DELTA_PROTECTION         -405050
#define MP_MM_PROTECTION_LIST_END       405051
#define MP_NOT_YET_INITIALIZED         -405052
#define MP_INFO_ERROR_STATE            -410000
#define MP_INFO_LOG_TOO_SMALL          -410002
#define MP_INFO_NO_TIMESTAMP           -410004
#define MP_INFO_LOG_UNKNOWN            -410006
#define MP_INFO_LOG_WRONG_SIZE         -410008
#define MP_INFO_TOO_MANY_DEALS         -410010
#define MP_INFO_POSS_DUPL              -410011
#define MP_INFO_TOO_MANY_LOGS          -410012
#define MP_INFO_UNDEFINED_STATE        -410014
#define MP_INFO_DEAL_DELAYED           -410015
#define MP_LOG_ALREADY_INIT             415001
#define MP_LOG_NOT_INITIALIZED         -415002
#define MP_LOG_NOT_READ_MODE           -415004
#define MP_LOG_NOT_WRITE_MODE          -415006
#define MP_LOG_END_OF_FILE             -415007
#define MP_LOG_UNDEFINED_MODE          -415008
#define MP_MATCH_ALRLOAD               -420001
#define MP_MATCH_DEFMAX                -420003
#define MP_MATCH_DISCARDED             -420005
#define MP_MATCH_ILL_CRS               -420007
#define MP_MATCH_MIN_QUANTITY          -420009
#define MP_MATCH_PREMIUM_REQ           -420011
#define MP_MATCH_TIMEOUT               -420013
#define MP_MATCH_INV_ALTER             -420015
#define MP_MATCH_NOT_IMPL              -420017
#define MP_MATCH_OVERBID               -420019
#define MP_MATCH_UNKNOWN               -420021
#define MP_MATCH_BID_ASK               -420023
#define MP_MATCH_VALIDITY              -420025
#define MP_MATCH_MARBOUNCE             -420027
#define MP_MATCH_PREMIUM               -420029
#define MP_MATCH_STOPPED               -420031
#define MP_MATCH_AONBOUNCE             -420033
#define MP_MATCH_BLOCK                 -420035
#define MP_MATCH_COMBO_MAX_LEGS        -420037
#define MP_MATCH_COMBO_PART            -420039
#define MP_MATCH_COMBO_SAVE            -420041
#define MP_MATCH_INV_COMBO_SIZE        -420043
#define MP_MATCH_QUANTITY              -420045
#define MP_MATCH_ORDER_EXISTS          -420047
#define MP_MATCH_NOT_AT_MARKET         -420049
#define MP_MATCH_LOW_VOLUME            -420051
#define MP_MATCH_BROKER_SPREAD         -420053
#define MP_MATCH_ILL_INTERBANK         -420055
#define MP_MATCH_ACC_PREMIUM           -420057
#define MP_MATCH_ACC_ORDER             -420059
#define MP_MATCH_COMBO_LEG             -420061
#define MP_MATCH_LEG_PRICE_NOT_0       -420063
#define MP_MATCH_LEG_NOT_FOUND         -420065
#define MP_MATCH_QUANT_NE_LEG          -420067
#define MP_MATCH_COMBO_SPREAD          -420069
#define MP_MATCH_SER_IS_EXPIRED        -420071
#define MP_MATCH_VOLUME_REQ            -420073
#define MP_MATCH_CROSS_NO_STDCOMB      -420074
#define MP_MATCH_ILL_ORDER_TYPE        -420076
#define MP_MATCH_MKT_ORDER_PRICE       -420078
#define MP_MATCH_NOCLS_PRM             -420079
#define MP_MATCH_FILL_BAL              -420081
#define MP_MATCH_COP_LESS              -420083
#define MP_MATCH_COP_VAR               -420085
#define MP_MATCH_PRE_TIME              -420087
#define MP_MATCH_INV_EXP               -420089
#define MP_MATCH_CROSS_PRICE           -420091
#define MP_MATCH_BLOCK_MAX_LEGS        -420093
#define MP_MATCH_BLOCK_SERIES          -420095
#define MP_MATCH_LMT_NOT_VAL           -420097
#define MP_MATCH_MKT_NOT_VAL           -420099
#define MP_MATCH_KIL_NOT_VAL           -420101
#define MP_MATCH_EXISTS_AS_STD_COMBO   -420103
#define MP_MATCH_EXISTS_AS_REV_STD_CBS -420105
#define MP_MATCH_TM_COMBO_EXISTS       -420107
#define MP_MATCH_REV_TM_COMBO_EXISTS   -420109
#define MP_MATCH_TOO_MANY_TM_COMBOS    -420111
#define MP_MATCH_ILL_RATIO             -420113
#define MP_MATCH_ILL_BUY_SELL_OP       -420115
#define MP_MATCH_COMBO_DIFF_CONTR_SIZE -420117
#define MP_MATCH_NO_BB_WHEN_TM_CBS_P   -420119
#define MP_MATCH_DUPL_SERIES           -420121
#define MP_MATCH_NOT_AUTHORIZED        -420123
#define MP_MATCH_NOTHEO_PRM            -420125
#define MP_MATCH_MIXED_COM             -420127
#define MP_MATCH_MEM_CRS_NOT_ALLOWED   -420129
#define MP_MATCH_PRICE_LIMIT           -420131
#define MP_MATCH_INV_STP_COND          -420133
#define MP_MATCH_INV_HIDDEN            -420135
#define MP_MATCH_INV_SHOWN             -420137
#define MP_MATCH_NOT_AUTH              -420139
#define MP_MATCH_SHOWN_TOO_SMALL       -420141
#define MP_MATCH_AONNOTVALID           -420143
#define MP_MATCH_INV_DELTA             -420145
#define MP_MATCH_FOK_NOT_WKUP_OWN      -420147
#define MP_MATCH_AON_CROSS_PRICE       -420149
#define MP_MATCH_LEG_PREMIUM           -420151
#define MP_MATCH_NO_WILD_CARD          -420153
#define MP_MATCH_INV_OP_CLS_REQ        -420155
#define MP_MATCH_INV_ORIGIN            -420157
#define MP_MATCH_INV_ACCOUNT           -420159
#define MP_MATCH_INV_CTI_CODE          -420161
#define MP_MATCH_NOT_AT_BEST           -420163
#define MP_MATCH_PRICE_LIMIT_LEG       -420165
#define MP_MATCH_PRICE_DEV_LEG         -420167
#define MP_MATCH_PRICE_LEG             -420169
#define MP_MATCH_PRICE_RANGE           -420171
#define MP_MATCH_NOT_TIME_YET          -420173
#define MP_MATCH_NO_ACTION              420175
#define MP_MATCH_ORD_NOT_FOU           -420177
#define MP_MATCH_CB_LIMIT_LAST         -420179
#define MP_MATCH_CB_LIMIT_REF          -420181
#define MP_MATCH_PERC_OR_ABS           -420183
#define MP_MATCH_BLMT_ORDER_PRICE      -420184
#define MP_MATCH_BLMT_NOT_VAL          -420185
#define MP_MATCH_BLMT_NO_PREM          -420187
#define MP_MATCH_NOT_IN_WORKUP         -420189
#define MP_MATCH_IN_WORKUP             -420191
#define MP_MATCH_INS_FILL_OR_KILL      -420193
#define MP_MATCH_SST_FILL_OR_KILL      -420195
#define MP_MATCH_USR_FILL_OR_KILL      -420197
#define MP_MATCH_INS_FILL_AND_KILL     -420199
#define MP_MATCH_SST_FILL_AND_KILL     -420201
#define MP_MATCH_USR_FILL_AND_KILL     -420203
#define MP_MATCH_INS_FILL_AND_STORE    -420205
#define MP_MATCH_SST_FILL_AND_STORE    -420207
#define MP_MATCH_USR_FILL_AND_STORE    -420209
#define MP_MATCH_INS_LIMIT_ORD         -420211
#define MP_MATCH_SST_LIMIT_ORD         -420213
#define MP_MATCH_USR_LIMIT_ORD         -420215
#define MP_MATCH_INS_MARKET_ORD        -420217
#define MP_MATCH_SST_MARKET_ORD        -420219
#define MP_MATCH_USR_MARKET_ORD        -420221
#define MP_MATCH_INS_ALL_OR_NONE       -420223
#define MP_MATCH_SST_ALL_OR_NONE       -420225
#define MP_MATCH_USR_ALL_OR_NONE       -420227
#define MP_MATCH_INV_INT_HIDDEN        -420229
#define MP_MATCH_OID_REQUIRED          -420231
#define MP_MATCH_ODD_LOT_EXP           -420233
#define MP_MATCH_ILL_ORDER_TYPE_SST    -420235
#define MP_MATCH_ILL_ORDER_TYPE_INT    -420237
#define MP_MATCH_ILL_ORDER_TYPE_USR    -420239
#define MP_MATCH_MIN_VOL_TRC           -420241
#define MP_MATCH_MAX_VOL_TRC           -420243
#define MP_MATCH_INS_IMBALANCE         -420245
#define MP_MATCH_SST_IMBALANCE         -420247
#define MP_MATCH_USR_IMBALANCE         -420249
#define MP_MATCH_INS_MTL_ROUND_LOT     -420251
#define MP_MATCH_SST_MTL_ROUND_LOT     -420253
#define MP_MATCH_USR_MTL_ROUND_LOT     -420255
#define MP_MATCH_INS_MTL_COMBO_R_LOT   -420257
#define MP_MATCH_SST_MTL_COMBO_R_LOT   -420259
#define MP_MATCH_USR_MTL_COMBO_R_LOT   -420261
#define MP_MATCH_INS_ODD_LOT           -420263
#define MP_MATCH_SST_ODD_LOT           -420265
#define MP_MATCH_USR_ODD_LOT           -420267
#define MP_MATCH_INS_LIMIT_ODD_LOT     -420269
#define MP_MATCH_SST_LIMIT_ODD_LOT     -420271
#define MP_MATCH_USR_LIMIT_ODD_LOT     -420273
#define MP_MATCH_INS_MARKET_ODD_LOT    -420275
#define MP_MATCH_SST_MARKET_ODD_LOT    -420277
#define MP_MATCH_USR_MARKET_ODD_LOT    -420279
#define MP_MATCH_INS_MTL_ODD_LOT       -420281
#define MP_MATCH_SST_MTL_ODD_LOT       -420283
#define MP_MATCH_USR_MTL_ODD_LOT       -420285
#define MP_MATCH_INS_HIDDEN_AGGRESSIVE -420287
#define MP_MATCH_SST_HIDDEN_AGGRESSIVE -420289
#define MP_MATCH_USR_HIDDEN_AGGRESSIVE -420291
#define MP_MATCH_INS_HIDDEN_PASSIVE    -420293
#define MP_MATCH_SST_HIDDEN_PASSIVE    -420295
#define MP_MATCH_USR_HIDDEN_PASSIVE    -420297
#define MP_MATCH_OVERRIDE_CRS          -420299
#define MP_MATCH_MATCHED_CRS_PRICE     -420301
#define MP_MATCH_BID_ORDER             -420303
#define MP_MATCH_ASK_ORDER             -420305
#define MP_MATCH_FORCE_ORDER           -420307
#define MP_MATCH_ILL_ORDER_TYPE_TX     -420309
#define MP_MATCH_MIN_BLK_SIZE          -420311
#define MP_MATCH_MAX_BLK_SIZE          -420313
#define MP_MATCH_INS_DECR_SHOWN_NOHIDD -420315
#define MP_MATCH_INS_DECR_SHOWN        -420317
#define MP_MATCH_INS_DECR_HIDD         -420319
#define MP_MATCH_INS_INCR_SHOWN        -420321
#define MP_MATCH_INS_INCR_HIDD         -420323
#define MP_MATCH_INS_CLIENT            -420325
#define MP_MATCH_INS_PRICE_IMPR        -420327
#define MP_MATCH_INS_PRICE_DISIMPR     -420329
#define MP_MATCH_INS_BLOCK             -420331
#define MP_MATCH_INS_TIME_EXT          -420333
#define MP_MATCH_INS_TIME_DECR         -420335
#define MP_MATCH_INS_ORDER_TYPE        -420337
#define MP_MATCH_INS_EXCH_ORDER_TYPE   -420339
#define MP_MATCH_ALTER_BALANCE         -420341
#define MP_MATCH_SST_DECR_SHOWN_NOHIDD -420343
#define MP_MATCH_SST_DECR_SHOWN        -420345
#define MP_MATCH_SST_DECR_HIDD         -420347
#define MP_MATCH_SST_INCR_SHOWN        -420349
#define MP_MATCH_SST_INCR_HIDD         -420351
#define MP_MATCH_SST_CLIENT            -420353
#define MP_MATCH_SST_PRICE_IMPR        -420355
#define MP_MATCH_SST_PRICE_DISIMPR     -420357
#define MP_MATCH_SST_BLOCK             -420359
#define MP_MATCH_SST_TIME_EXT          -420361
#define MP_MATCH_SST_TIME_DECR         -420363
#define MP_MATCH_SST_ORDER_TYPE        -420365
#define MP_MATCH_SST_EXCH_ORDER_TYPE   -420367
#define MP_MATCH_CRS_PRIO_NO_ORDER     -420369
#define MP_MATCH_SST_PST_ORDER         -420371
#define MP_MATCH_INS_PST_ORDER         -420373
#define MP_MATCH_USR_PST_ORDER         -420375
#define MP_MATCH_SST_SHORT_ORDER       -420377
#define MP_MATCH_INS_SHORT_ORDER       -420379
#define MP_MATCH_USR_SHORT_ORDER       -420381
#define MP_MATCH_SST_MB_ORDER          -420383
#define MP_MATCH_INS_MB_ORDER          -420385
#define MP_MATCH_USR_MB_ORDER          -420387
#define MP_MATCH_SST_BL_ORDER          -420389
#define MP_MATCH_INS_BL_ORDER          -420391
#define MP_MATCH_USR_BL_ORDER          -420393
#define MP_MATCH_LAST_PRICE            -420395
#define MP_MATCH_MB_SELL               -420397
#define MP_MATCH_MB_ORDER_TYPE         -420399
#define MP_MATCH_SH_BUY                -420401
#define MP_MATCH_SH_TKO                -420403
#define MP_MATCH_MTL_NO_OPPOSING       -420405
#define MP_MATCH_COMBO_PRACTICE        -420407
#define MP_MATCH_COMBO_EQTY_NOT_MULT   -420409
#define MP_MATCH_RELOAD_NOT_DONE       -420410
#define MP_MATCH_FOK_FAK_NOT_ALLOWD    -420411
#define MP_MATCH_VOL_VAL_TRC           -420413
#define MP_MATCH_BEST_LIMIT_REQ        -420415
#define MP_MATCH_SER_WILD_CARD         -420417
#define MP_MATCH_INV_ACTIVATION        -420419
#define MP_MATCH_INV_CLEARING_PART     -420421
#define MP_MATCH_INV_E_ORD_TYPE_PRIO   -420423
#define MP_MATCH_INV_ALWAYS_INACTIVE   -420425
#define MP_MATCH_ILL_EXCH_ORDER_TYPE   -420426
#define MP_MATCH_MM_PRIO_LEVEL_EXC     -420427
#define MP_MATCH_STOP_PREMIUM          -420429
#define MP_MATCH_SST_SSO_OPEN_END      -420431
#define MP_MATCH_INS_SSO_OPEN_END      -420433
#define MP_MATCH_USR_SSO_OPEN_END      -420435
#define MP_MATCH_SST_SSO_CLOSE_END     -420437
#define MP_MATCH_INS_SSO_CLOSE_END     -420439
#define MP_MATCH_USR_SSO_CLOSE_END     -420441
#define MP_MATCH_SST_SSO               -420443
#define MP_MATCH_INS_SSO               -420445
#define MP_MATCH_USR_SSO               -420447
#define MP_MATCH_NO_SST_FOR_SSO        -420449
#define MP_MATCH_SSO_SPEC_NO_TYPE      -420451
#define MP_MATCH_SST_EXT_T_NOT_VALID   -420453
#define MP_MATCH_SST_EXT_T_STATE       -420455
#define MP_MATCH_INS_EXT_T_STATE       -420457
#define MP_MATCH_INS_STOP_ORD          -420459
#define MP_MATCH_SST_STOP_ORD          -420461
#define MP_MATCH_USR_STOP_ORD          -420463
#define MP_MATCH_INS_CRS_SPREAD_MAR    -420465
#define MP_MATCH_SST_CRS_SPREAD_MAR    -420467
#define MP_MATCH_USR_CRS_SPREAD_MAR    -420469
#define MP_MATCH_INS_CRS_SPREAD_LIM    -420471
#define MP_MATCH_SST_CRS_SPREAD_LIM    -420473
#define MP_MATCH_USR_CRS_SPREAD_LIM    -420475
#define MP_MATCH_INS_UNDISCLOSED_QTY   -420477
#define MP_MATCH_SST_UNDISCLOSED_QTY   -420479
#define MP_MATCH_USR_UNDISCLOSED_QTY   -420481
#define MP_MATCH_MIN_UNDISCLOSED       -420483
#define MP_MATCH_CP_NO_HIDDEN          -420485
#define MP_MATCH_CP_LIMIT              -420487
#define MP_MATCH_NO_CP_PRICE           -420489
#define MP_MATCH_MIN_VOLUME_MATCH      -420491
#define MP_MATCH_MIN_VOLUME_FIX        -420493
#define MP_MATCH_FIX_PREMIUM_DIFF      -420495
#define MP_MATCH_UNDSC_NO_HIDDEN       -420497
#define MP_MATCH_UNDSC_NO_MARKET       -420499
#define MP_MATCH_INTCRSONUSER          -420501
#define MP_MATCH_MUST_BE_QUOTE         -420503
#define MP_MATCH_ILL_NAMED_STRUCTURE   -420505
#define MP_MATCH_INCONSISTENT_VIM      -420507
#define MP_MATCH_ILL_QUOTE_ACTION      -420509
#define MP_MATCH_ILL_PRICE_QUANTITY    -420511
#define MP_MATCH_INV_ORDER_CAPACITY    -420513
#define MP_MATCH_INV_ALT_CLEARING      -420515
#define MP_MATCH_MAX_QUANTITY_OSA      -420517
#define MP_MATCH_DUPL_NAMED_STRUCT     -420519
#define MP_MATCH_MAND_NAMED_STRUCT     -420521
#define MP_MATCH_LINKED_ORDER_CONT     -420523
#define MP_MATCH_LINKED_ORDER_DUPL_SER -420525
#define MP_MATCH_LINKED_ORDER_MIN_LEGS -420527
#define MP_MATCH_LINKED_ORDER_MAX_LEGS -420529
#define MP_MATCH_INV_ALTER_LINKED      -420531
#define MP_MATCH_NOT_SAME_LOTS         -420533
#define MP_MATCH_ONLY_ONE_ORDER        -420535
#define MP_MATCH_INV_DELTA_QUANTITY    -420537
#define MP_MATCH_HOLD_IN_MARKET        -420539
#define MP_MATCH_USER_NO_TRADE         -420541
#define MP_MATCH_IPMO_RESTRICTIONS     -420543
#define MP_MATCH_MULTI_PRICE_TYPE      -420545
#define MP_MATCH_NO_COMBO_IN_MULTI     -420547
#define MP_MATCH_MULTI_ORDER_DUPL_SER  -420549
#define MP_MATCH_PRICE_TYPE_SAME_SIDE  -420551
#define MP_MATCH_INV_CALC_QUANTITY     -420553
#define MP_MATCH_PRICE_TYPE_SAME_UNIT  -420555
#define MP_MATCH_MULTI_ORDER_MIN_LEGS  -420557
#define MP_MATCH_MULTI_ORDER_MAX_LEGS  -420559
#define MP_MATCH_MULTI_ORDER_CONT      -420561
#define MP_MATCH_PRICE_TYPE_ILL_UNIT   -420563
#define MP_MATCH_PRICE_TYPE_ILL_PQF    -420565
#define MP_MATCH_ORDER_SIZE_TOO_LARGE  -420567
#define MP_MATCH_USR_RISK_BREACHED     -420569
#define MP_MATCH_MAX_ORDER_RATE        -420571
#define MP_MATCH_ORDER_SUBMISSION      -420573
#define MP_MATCH_NO_SPONSOR            -420575
#define MP_MATCH_MUST_BE_ORDER         -420577
#define MP_MATCH_ORDER_VALUE_TOO_LARGE -420579
#define MP_MATCH_ORDER_SIZE_GT_AVAILQ  -420581
#define MP_MATCH_NO_EXCHANGE_INFO      -420583
#define MP_MATCH_CLIENT_CAT_INVALID    -420585
#define MP_MATCH_EXCLIENT_BLANK        -420587
#define MP_MATCH_ILL_PREMIUM_FIXED     -420589
#define MP_MATCH_NO_FIXED_PRICE        -420591
#define MP_MATCH_FIXED_PRICE_COMBO     -420593
#define MP_MATCH_ILL_TIME_FIXED_MARKET -420595
#define MP_MATCH_TRP_FIXED_LINKED_LTP  -420597
#define MP_MATCH_SST_PR_ORDER          -420599
#define MP_MATCH_INS_PR_ORDER          -420601
#define MP_MATCH_USR_PR_ORDER          -420603
#define MP_MATCH_ILL_PR_VALUE          -420605
#define MP_MATCH_SH_COMPRICE           -420607
#define MP_MATCH_MKT_BLMT_NOPRC_EXIST  -420609
#define MP_MATCH_SH_ORDTYPE            -420611
#define MP_MATCH_SH_LTP_NEUFALL        -420613
#define MP_MATCH_RFQ_NOT_LEGITIMATE    -420615
#define MP_MATCH_RFQ_RESPONSE_ILLEGAL  -420617
#define MP_MATCH_MIN_VALUE_MIDPOINT    -420619
#define MP_MATCH_SST_MIDPOINT          -420621
#define MP_MATCH_SH_ILL_COMBO          -420623
#define MP_MATCH_FOK_NOT_ALLOWD        -420625
#define MP_MATCH_MAX_VALUE_MIDPOINT    -420627
#define MP_MATCH_INS_GOOD_TILL_SESSION -420629
#define MP_MATCH_SST_GOOD_TILL_SESSION -420631
#define MP_MATCH_USR_GOOD_TILL_SESSION -420633
#define MP_MATCH_TAR_INST_NOT_TRADED   -420635
#define MP_MATCH_TRIGGER_NOT_ALLOWED   -420637
#define MP_MATCH_GIVE_UP_ACCOUNT_EXIST -420639
#define MP_OB_INV_HANDLE               -425000
#define MP_OB_NO_RESOURCE              -425002
#define MP_OB_NOT_COSTUMER             -425003
#define MP_OB_NOT_INIT                 -425004
#define MP_OB_NOT_LOCKED               -425006
#define MP_OB_NOT_SERIES               -425007
#define MP_OB_OLD_CUSTOMER             -425009
#define MP_OB_OLD_SERIES               -425011
#define MP_OB_END                       425013
#define MP_OB_TENTATIVE                 425015
#define MP_OB_NOT_CUSTOMER             -425017
#define MP_OB_NOT_UPDATER              -425018
#define MP_OB_FM_FAIL                  -425020
#define MP_OB_SER_COMBO_PART           -425021
#define MP_RTR_ERROR                   -430001
#define MP_RTR_ALRCRE                  -430003
#define MP_RTR_NULLIOB                 -430005
#define MP_RTR_NODST                   -430007
#define MP_RTR_TXTIMOUT                -430009
#define MP_RTR_RCVTIMOUT               -430011
#define MP_QUERY_CUST_IST              -435001
#define MP_QUERY_NOT_OWN               -435003
#define MP_QUERY_CUST_UND              -435005
#define MP_QUERY_OID_NOTFND            -435007
#define MP_QUERY_FAIL                  -435008
#define MP_QUERY_ONLY_THIS_SER         -435009
#define MP_QUERY_NOT_AUTH              -435011
#define MP_QUERY_DATAINCOMPLETE        -435012
#define MP_QUERY_DELTA_LIMITS_INVALID  -435013
#define MP_QUEUE_LAST_ENTRY             440001
#define MP_QUEUE_EMPTY                 -440003
#define MP_QUEUE_FULL                  -440005
#define MP_QUEUE_NOT_INIT              -440007
#define MP_QUEUE_SIZE_ERROR            -440008
#define MP_QUEUE_NOT_REMOVED           -440009
#define MP_STAT_INSFMEM                -445000
#define MP_STAT_INT_OVRFLW             -445002
#define MP_PBLOG_NO_LOGB_NAME          -450000
#define MP_TXSRV_TIMEOUT               -455001
#define MP_TXSRV_NOT_CONN              -455003
#define MP_MXABS_BAD_ATTRIBUTE         -460000
#define MP_MXABS_OK                     460001
#define MP_MXABS_INVHANDLE             -460003
#define MP_MXABS_INVLEN                -460005
#define MP_MXABS_NOTFND                -460007
#define MP_MXABS_NYI                   -460009
#define MP_MXABS_NOOP4CLIENT           -460011
#define MP_MXABS_NOACCESS              -460013
#define MP_MXABS_NOACTION              -460015
#define MP_MXABS_NOREPORT              -460017
#define MP_MXABS_ALROPEN               -460019
#define MP_MXABS_INVEXERPT             -460021
#define MP_MXABS_SUBJ2DLL              -460023
#define MP_MXABS_INVTXCODE             -460024
#define MP_MXABS_ZEROQTY               -460025
#define MP_MXABS_BADQTY4REM            -460027
#define MP_MXABS_SYNCINPROG            -460029
#define MP_MXABS_DLLINPROG             -460031
#define MP_MXABS_ALRRES                -460033
#define MP_MXABS_NOTRES                -460035
#define MP_MXABS_TRADERSUSP            -460037
#define MP_MXABS_CXLREPLMENT           -460039
#define MP_MXABS_OPMISMATCH            -460041
#define MP_MXABS_ALERT                 -460043
#define MP_MXABS_OK_BUT_WAIT            460045
#define MP_MXAOF_INTERR                -465000
#define MP_MXAOF_COMERR                -465002
#define MP_MXAOF_NOLOG                 -465004
#define MP_MXAOF_MSG_REROUTED          -465005
#define MP_MXAOF_MSG_IGNORED           -465006
#define MP_MXAOF_SEQ_NO_TO_AOF          465007
#define MP_MXAOF_SEQ_NO_FROM_AOF        465009
#define MP_MXFLT_INTERR                -470000
#define MP_MXFLT_COMERR                -470002
#define MP_MXFLT_NOLOG                 -470004
#define MP_MXFLT_DATAERR               -470006
#define MP_MXFLT_HANDLERR              -470008
#define MP_MXFLT_NOTSPEC               -470010
#define MP_MXFLT_NOTFOUND              -470012
#define MP_MXFLT_FILTERR               -470014
#define MP_QXSRV_ILL_MIXED_INV_PRICES  -475001
#define MP_QXSRV_ILL_MIXED_PRICE_TYPES -475003
#define MP_QXSRV_ILL_NO_COMBO_LEGS     -475005
#define MP_QXSRV_NON_EXISTING          -475007
#define MP_QXSRV_NOT_ALLOWED           -475009
#define MP_QXSRV_NOT_ALLOWED_TO_ANSWER -475011
#define MP_QXSRV_NOT_ALLOWED_TO_EXE    -475013
#define MP_QXSRV_QUOTE_MISSING         -475015
#define MP_QXSRV_STATE_NOT_ACCEPTING   -475017
#define MP_QXSRV_STATE_NOT_IN_TRADING  -475019
#define MP_QXSRV_TOO_LONG_ACCEPT_TIMER -475021
#define MP_QXSRV_TOO_LONG_TRADE_TIMER  -475023
#define MP_QXSRV_VOLUME_TOO_SMALL      -475025
#define MP_QXSRV_MAX_NO_COMBO_LEGS     -475027
#define MP_QXSRV_EXE_PREMIUM_DIFF      -475029
#define MP_QXSRV_NO_REPLY              -475031
#define MP_QXSRV_COMBO_NOT_ALLOWED     -475033
#define MP_QXSRV_QUANTITY_MISMATCH     -475035
#define MP_QXSRV_ACCOUNT               -475037
#define MP_QXSRV_INV_DEALSOURCE        -475039
#define MP_QXSRV_INV_VAILDATE_ACCOUNT  -475041
#define MP_QXSRV_CRS_PRIO_SPREAD       -475043
#define MP_QXSRV_CRS_PRIO_SPREAD_TIME  -475045
#define MP_QXSRV_CRS_PRIO_NOT_ALLOWED  -475047
#define MP_QXSRV_TRP_INI_NOT_ALLOWED   -475049
#define MP_QXSRV_TRP_INI_INTERBANK     -475051
#define MP_QXSRV_TRP_INI_MIN_VAL       -475053
#define MP_QXSRV_TRP_FOR_NOT_ALLOWED   -475055
#define MP_QXSRV_TRP_INV_DATE          -475057
#define MP_QXSRV_TRP_INV_RATE          -475059
#define MP_QXSRV_TRP_INV_BOQ           -475061
#define MP_QXSRV_TRP_COMB_NOT_ALLOWED  -475063
#define MP_QXSRV_TRP_MIN_VAL           -475065
#define MP_QXSRV_TRP_MAX_VAL           -475067
#define MP_QXSRV_TRP_COMB_LEGS         -475069
#define MP_QXSRV_TRP_INV_PARTY         -475071
#define MP_QXSRV_TRP_INV_EXTEND_PRICE  -475073
#define MP_QXSRV_CPPX_NO_MAX_TIME      -475074
#define MP_QXSRV_CPPX_NOT_INIT         -475076
#define MP_QXSRV_CPPX_MAX_TIME_PASSED  -475078
#define MP_QXSRV_CPPX_INV_SERIES       -475080
#define MP_QXSRV_CPPX_INV_QUANTITY     -475082
#define MP_QXSRV_CPPX_INV_PARTICIPANT  -475084
#define MP_QXSRV_NON_STD_SETTL_ALLOWED -475085
#define MP_QXSRV_INVQTYINCR            -475086
#define MP_OHS_INVMEMBER               -485000
#define MP_OHS_INVPARTY                -485002
#define MP_OHS_INVTIME                 -485004
#define MP_OHS_TXNOTHANDLED            -485006
#define MP_OHS_INVTRANSSIZE            -485008
#define MP_OHS_INVBIDASK               -485010
#define MP_OHS_INVINSTANCE             -485012
#define MP_OHS_DATAINCOMPLETE          -485014
#define MP_OHS_INVBDXTYPE              -485016
#define MP_OHS_INVORDERNBR             -485018
#define MP_OHS_DATAPURGED               485019
#define MP_OHS_INVSERIES                485021
#define MP_OHS_DATANOTREADY             485023
#define MP_OHS_DATAINCOMPLETE_NORECOV  -485024

/******************************************************************************
*end*of* mp_messages.h
*******************************************************************************/

#endif /* _MP_MESSAGES_H_ */


#ifndef _OMN_MESSAGES_H_
#define _OMN_MESSAGES_H_

/******************************************************************************
Module: omn_messages.h

Message definitions generated 2020-10-21 15:24:26 by amt, version 3.19.7.0 - Built: 2017-12-30.

NOTE: Do not edit this file. It is automatically generated from
      one or more message files.
*******************************************************************************/

#define OMN_GENERIC_DBG                 200001
#define OMN_GENERIC_SUCCESS             200003
#define OMN_GENERIC_INFO                200005
#define OMN_GENERIC_WARN               -200007
#define OMN_GENERIC_ERROR              -200008
#define OMN_GENERIC_FATAL              -200010
#define OSA_RELOGIN_NOT_ALLOWED        -201000
#define OMN_REGISTRATION_NOT_ALLOWED    202001
#define OMN_USER_NOT_FOUND              202003
#define OMN_USERTYPE_NOT_FOUND          202005
#define OMN_FAILED_TO_BUILD_VERTABLE    202007
#define OMN_NODEID_NOT_FOUND            202009
#define OMN_OSA_SEC_OMDU_INVLOGIN      -204000
#define OMN_OSA_SEC_INVLOGIN_1         -204002
#define OMN_OSA_SEC_INVLOGIN_2         -204004
#define OMN_OSA_SEC_INVLOGIN_3         -204005
#define OMN_OSA_SEC_INVLOGIN_4          204007
#define OMN_OSA_SEC_INVLOGIN_5          204009
#define OMN_OSA_SEC_INVLOGIN_6          204011
#define OMN_OSA_SEC_INVLOGIN_7          204013
#define OMN_OSA_SEC_INVLOGIN_8          204015
#define OMN_OSA_SEC_INVLOGIN_9          204017
#define OMN_OSA_SEC_INVLOGIN_10         204019
#define OMN_OSA_SEC_INVLOGIN_11         204021
#define OMN_OSA_SEC_INVLOGIN_12         204023
#define OMN_OSA_SEC_INVLOGIN_13         204025
#define OMN_OSA_SEC_INVLOGIN_15         204027
#define OMN_OSA_SEC_INVLOGIN_16        -204028
#define OMN_OSA_SEC_INVLOGIN_17         204029
#define OMN_OSA_SEC_INVLOGIN_19         204031
#define OMN_OSA_SEC_INVLOGIN_20         204033
#define OMN_OSA_SEC_INVLOGIN_21         204035
#define OMN_OSA_SEC_INVLOGIN_22         204037
#define OMN_OSA_SEC_INVLOGIN_23         204039
#define OMN_OSA_SEC_INVLOGIN_24         204041
#define OMN_OSA_SEC_INVLOGIN_25         204043
#define OMN_OSA_SEC_INVLOGIN_26         204045
#define OMN_OSA_SEC_INVLOGIN_27         204047
#define OMN_OSA_SEC_INVLOGIN_28        -204049
#define OMN_OSA_SEC_INVLOGIN_29         204051
#define OMN_OSA_SEC_INVLOGIN_30        -204052
#define OMN_OSA_SEC_INVLOGIN_31        -204054
#define OMN_OSA_SEC_INVLOGIN_32        -204056
#define OMN_OSA_SEC_INVLOGIN_33        -204058
#define OMN_OSA_SEC_INVLOGIN_34        -204060
#define OMN_OSA_SEC_INVLOGIN_35        -204062
#define OMN_OSA_SEC_SET_SRC_FAILED     -204064
#define OMN_OSA_SEC_SET_PASSW_FAILED   -204066
#define OMN_OSA_SEC_SECVIO_1           -204068
#define OMN_OSA_SEC_SECVIO_2           -204070
#define OMN_OSA_SEC_OAPIOLD            -204072
#define OMN_OSA_SEC_INVNODEID_2        -204074
#define OMN_OSA_SEC_INVNODEID_3        -204076
#define OMN_OSA_SEC_INVNODEID_4        -204078
#define OMN_OSA_SEC_INVNODEID_8        -204080
#define OMN_OSA_SEC_INVNODEID_9        -204082
#define OMN_OSA_SEC_INVNODEID_10       -204084
#define OMN_OSA_SEC_INVNODEID_11       -204086
#define OMN_OSA_SEC_IN_STARTUP_MODE     204087
#define OMN_OSA_SEC_IN_FAILOVER_MODE    204089
#define OMN_OSA_SEC_QUERY_SELF          204091
#define OMN_OSA_SEC_INV_OQ62            204093
#define OMN_OSA_SEC_INV_OQ6X            204095
#define OMN_OSA_SEC_INV_OQ50            204097
#define OMN_OSA_SEC_INV_NQ10            204099
#define OMN_OSA_SEC_INV_NQ11            204101
#define OMN_OSA_SEC_INV_QRY             204103
#define OMN_OSA_SEC_INV_SETPWD_TRX_1   -204104
#define OMN_OSA_SEC_INV_SETPWD_TRX_2   -204106
#define DUGWY_NOCFGFILE                -207001
#define DUGWY_INTERR                   -207002
#define DUGWY_NORMTSRVNODES            -207004
#define DUGWY_NORMTSRV                 -207006
#define DUGWY_NOMBRNODES               -207008
#define DUGWY_INFGRPEXISTS             -207010
#define DUGWY_NOINFGRP                 -207012
#define DUGWY_NOFILTER                 -207014
#define DUGWY_CFGSTRLNG                -207016
#define DUGWY_NOSRVTCPIP               -207018
#define DUGWY_NOMEMBER                 -207020
#define DUGWY_INVGWYMSG                -207022
#define DUGWY_INVGWYVRS                -207024
#define DUGWY_INSUFMEM                 -207026
#define DUGWY_ABORT                    -207028
#define DUGWY_NOOPMAP                  -207029
#define DUGWY_EOFFND                    207031
#define DUGWY_CLTQUETOLONG             -207033
#define DUGWY_UNKNOWN                   207035
#define DUGWY_NOPREFNODES              -207037
#define DUGWY_DUPCFGNODES              -207039
#define DUGWY_INVCFGBLOCK              -207041
#define DUGWY_CMDNOTALLOW              -207043
#define DUGWY_SERVERNOTFOUND           -207045
#define DUGWY_INVCONFIG                -207046
#define DUGWY_NOSRVGROUPS              -207047
#define DUGWY_NOMEMBERS                -207049
#define OMDU_OPENSOCK                  -208000
#define OMDU_DATALOST                  -208002
#define OMDU_LINKLOST                  -208004
#define OMDU_SENDERLOST                -208006
#define OMDU_SENDERRESTARTED           -208008
#define OMDU_NONODADDR                 -208010
#define OMDU_NONODENAME                -208012
#define OMDU_NORDACCESS                -208014
#define OMDU_NOTTWOCALLBACK            -208016
#define OMDU_INSFMEM                   -208018
#define OMDU_INVTHRCNTX                -208020
#define OMDU_CLTPRTERR                 -208022
#define OMDU_CLTLNKLOST                -208024
#define OMDU_INVVALSYNTAX              -208026
#define OMDU_TOMUCHDATA                -208028
#define OMDU_INVVERSTR                 -208030
#define OMDU_WRGVERS                   -208032
#define OMDU_INFOBJNAMWLD              -208034
#define OMDU_SNDNAMLNG                 -208036
#define OMDU_FAILTODCLSRV              -208038
#define OMDU_NOUPDFLG                  -208040
#define OMDU_XCHN                      -208042
#define OMDU_ETHCOMPRD                 -208044
#define OMDU_ETHCOMPXTA                -208046
#define OMDU_INFCLSNOTVLD              -208048
#define OMDU_INTERR                    -208050
#define OMDU_SNDRUNAVL                 -208052
#define OMDU_RETRNSNOTFND              -208054
#define OMDU_SNDRCFG                   -208056
#define OMDU_TOLNGPNDRCVQUE            -208058
#define OMDU_NOTRUNNING                -208060
#define OMDU_THRSTALLED                -208062
#define OMDU_NORCVRCLT                 -208064
#define OMDU_SCRPTNOTENA               -208066
#define OMDU_MAXINFCLS                 -208068
#define OMDU_NOINFCLS                  -208070
#define OMDU_INVINFCLS                 -208072
#define OMDU_NOVLDADRSTR               -208074
#define OMDU_FLOODED                   -208075
#define OMDU_NOTFLOODED                -208077
#define OMDU_MAXSUB                    -208079
#define OMDU_NOMOREMSGS                -208081
#define OMDU_MOREMSGS                  -208083
#define OMDU_XTASIZENOLL               -208084
#define OMDU_CLTQUETOLNG               -208086
#define OMDU_NOGSTHR                   -208088
#define OMDU_GBLSECUPD                 -208090
#define CACHE_QRYNOCFG                 -209000
#define CACHE_QRYNOAVAIL               -209002
#define CACHE_OVFLOW                   -209004
#define CACHE_COMERR                   -209006
#define CACHE_CFGERR                   -209008
#define CACHE_INTERR                   -209010
#define CACHE_MAXCLI                   -209012
#define CACHE_OKIDOKI                   209013
#define CACHE_FLTREQLOAD               -209015
#define CACHE_BDXNOAVAIL               -209017
#define CACHE_TRXNOAVAIL               -209019
#define CACHE_INSTRCLSREQ              -209021
#define OFS_FUNCTION_IS_OFF             209501
#define OFS_QUERY_INPUT_DATA_LEVEL      209503
#define OFS_QUERY_INPUT_DATA_VARIANT    209505
#define OFS_QUERY_INPUT_SAVE_ACTION     209507
#define OFS_QUERY_FILE_NAME             209509
#define OFS_QUERY_INPUT_FILE_NAME       209511
#define OFS_QUERY_INPUT_DATA_AUTHORITY  209513
#define OFS_QUERY_ANSWER_BUFF_SMALL    -209515
#define OFS_QUERY_SEGMENT_NBR_ZERO      209517
#define OFS_QUERY_PUT_ERROR_1           209519
#define OFS_QUERY_PUT_ERROR_2           209521
#define OFS_QUERY_PUT_ERROR_3           209523
#define OFS_QUERY_PUT_READ_RESULT      -209524
#define OFS_QUERY_FILE_NOT_EXIST        209525
#define OFS_SERVER_INTERNAL_ERROR_1    -209526
#define OFS_SERVER_INTERNAL_ERROR_2    -209528
#define OFS_INVALID_QUERY              -209530
#define OFS_NO_MORE_DATA                209531
#define OFS_FILE_DELETE_SUCCEEDED      -209533
#define OFS_OSS_POSIX_STAT_FAILED      -209535
#define OFS_OSS_POSIX_MKDIR_FAILED     -209537
#define OFS_OSS_POSIX_OPENDIR_FAILED   -209539
#define OFS_OSS_POSIX_ROPEN_FAILED     -209541
#define OFS_OSS_POSIX_READ_FAILED      -209543
#define OFS_OSS_POSIX_WOPEN_FAILED     -209545
#define OFS_OSS_POSIX_WRITE_FAILED     -209547
#define OFS_OSS_POSIX_RM_FAILED        -209549
#define OFS_OSS_POSIX_STD_EXCEPTION    -209551
#define OFS_OSS_POSIX_OTH_EXCEPTION    -209553
#define DBSRV_SS_ERROR                 -210500
#define DBSRV_SS_NORMAL                 210501
#define DBSRV_SS_BUFFEROVF             -210502
#define DBSRV_RMS_RNF                  -210504
#define DBSRV_RMS_EOF                  -210506
#define DBSRV_UNKNOWN_TBL_REQ_TYPE     -210508

/******************************************************************************
*end*of* omn_messages.h
*******************************************************************************/

#endif /* _OMN_MESSAGES_H_ */


#ifndef _PS_MESSAGES_H_
#define _PS_MESSAGES_H_

/******************************************************************************
Module: ps_messages.h

Message definitions generated 2020-10-21 15:24:31 by amt, version 3.19.7.0 - Built: 2017-12-30.

NOTE: Do not edit this file. It is automatically generated from
      one or more message files.
*******************************************************************************/

#define PS_NORMAL                       1900001
#define PS_INTERR                      -1900002
#define PS_FUTBUSDATE                  -1900004
#define PS_BUSNOTTOD                   -1900006
#define PS_INVSTARTDATEFMT             -1900008
#define PS_INVENDDATEFMT               -1900010
#define PS_INVOFFICIALFMT              -1900012
#define PS_PERIODNOTZERO               -1900014
#define PS_INVOFFBATLOG                -1900016
#define PS_BATLOGNOTFND                -1900018
#define PS_TERMSTRUCTCURVENOTFND       -1900020
#define PS_INVBUSDATFMT                -1900022
#define PS_INVCOUNTRYIDFMT             -1900024
#define PS_SERIESNOTFND                -1900026
#define PS_CURVENOTFND                 -1900028
#define PS_PRIMARYCURVENOTFND          -1900030
#define PS_SECONDARYCURVENOTFND        -1900032
#define PS_CFMNOTFND                   -1900034
#define PS_SERIESORCURVE               -1900036
#define PS_DAYCOUNTCONVNOTZERO         -1900038
#define PS_DISCMETHODNOTBLANK          -1900040
#define PS_SERIESNOTZERO               -1900042
#define PS_COUNTRYIDBLANK              -1900044
#define PS_CURVEIDBLANK                -1900046
#define PS_ENDNOTLATERSTART            -1900048
#define PS_STARTBEFOREBUS              -1900050
#define PS_PERIODLESSTHAN1             -1900052
#define PS_PERIODNOTMULT30             -1900054
#define PS_WRONGRUNTYPE                -1900056
#define PS_INVFROMDATEFMT              -1900058
#define PS_INVTODATEFMT                -1900060
#define PS_NOTACTIVE                   -1900062
#define PS_SUSPENDED                   -1900064
#define PS_EXPIRED                     -1900066
#define PS_NOPRICEPARAMSCONFIGURATION  -1900068
#define PS_INVALIDTIMESTAMP            -1900070
#define PS_INVALIDOPERATION            -1900072
#define PS_INVALIDDECIMALSVALUE        -1900074
#define PS_NOSNAPSHOT                  -1900076
#define PS_NOPRICECOLLECTION           -1900078
#define PS_INVSNAPSHOTRUNTYPE          -1900080
#define PS_NOTSAMERUNTYPE              -1900082
#define PS_INVCOLLECTIONPRICETYPE      -1900084
#define PS_NOSNAPSHOTCREATE            -1900086
#define PS_NOMARKET                    -1900088
#define PS_INVMARKET                   -1900090
#define PS_NOSNAPSHOTID                -1900092
#define PS_NOCOLLECTIONID              -1900094
#define PS_NOSERIESNAME                -1900096
#define PS_ABSWRNLEVEL                 -1900098
#define PS_PERWRNLEVEL                 -1900100
#define PS_INVALIDSTATECHANGE          -1900102
#define PS_INSNOTOPTION                -1900104
#define PS_INSNOTFUTURE                -1900106
#define PS_INVOPTIONTYPE               -1900108
#define PS_INVBOUGHTORSOLD             -1900110
#define PS_ONEITEMALLOWED              -1900112
#define PS_INVALIDSEQVALUE             -1900114
#define PS_INVALIDVALUATIONDATE        -1900116
#define PS_BATCHNOTCOMPLETED           -1900118
#define PS_OLDSNAPSHOT                 -1900120
#define PS_OLDPRICECOLLECTION          -1900122
#define PS_INVALIDSNAPSHOTPRICETYPE    -1900124
#define PS_INVALIDPRICEATTRIBUTE       -1900126
#define PS_NOWORKINPROGRESS            -1900128
#define PS_INVNAMEDSTRUCTCOMB          -1900130
#define PS_BARRIERNOTSUPPORTED         -1900132
#define PS_INVWORKINPROGRESSVALUE      -1900134
#define PS_BATCHLOCKED                 -1900136
#define PS_FOUREYECONTROL              -1900138
#define PS_INVALIDPRICESOURCETYPE      -1900140
#define PS_OVERRIDEONLYMANUAL          -1900142
#define PS_STRIKEPRICEZERO             -1900144
#define PS_RISKFREERATETOLARGE         -1900146
#define PS_DIVIDENDYIELDTOLARGE        -1900148
#define PS_INVCOLIDEXTREF              -1900150
#define PS_VOLATILITYNEGATIVE          -1900152
#define PS_NOCOLIDEXTREF               -1900154
#define PS_NOPRIVATEPRICELISTID        -1900156
#define PS_INVPRIVATEPRICELISTID       -1900158
#define PS_NOPRIVATEPRICELIST          -1900160
#define PS_RQ65DEPRECATED              -1900162
#define PS_RC65DEPRECATED              -1900164
#define PS_NODATEVIM                   -1900166
#define PS_UNDERLYINGNEGATIVE          -1900168
#define PS_STRIKENEGATIVE              -1900170
#define PS_KNOCKOUTNEGATIVE            -1900172
#define PS_DIVIDENDYIELDNEGATIVE       -1900174
#define PS_INTERESTRATENEGATIVE        -1900176
#define PS_INVPRICEVALIDATIONTYPE      -1900178
#define PS_INVISSUEDATE                -1900180
#define PS_KEEPDAYSNEGATIVE            -1900182
#define PS_INVPRIVATEPRICELISTBASE     -1900184
#define PS_NOTPUBLISHED                -1900186
#define PS_RC316DEPRECATED             -1900188
#define PS_SNAPSHOTCOPYNOTALLOWED      -1900190
#define PS_COLLECTIONCANNOTBEUPDATED   -1900192
#define PS_INVTORTPLUSONE              -1900194
#define PS_INVSESSION                  -1900196

/******************************************************************************
*end*of* ps_messages.h
*******************************************************************************/

#endif /* _PS_MESSAGES_H_ */


#ifndef _RI_MESSAGES_H_
#define _RI_MESSAGES_H_

/******************************************************************************
Module: ri_messages.h

Message definitions generated 2020-10-21 15:24:31 by amt, version 3.19.7.0 - Built: 2017-12-30.

NOTE: Do not edit this file. It is automatically generated from
      one or more message files.
*******************************************************************************/

#define RI_NORMAL                       900001
#define RI_NYI                         -900002
#define RI_BADMEMBER                   -900004
#define RI_PANIC                       -900006
#define RI_BADSIZE                     -900008
#define RI_BADFORMAT                   -900010
#define RI_TOOMUCHDATA                 -900012
#define RI_ITEXC                       -900014
#define RI_INVPAR                      -900016
#define RI_RANGERR                     -900018
#define RI_NOMEM                       -900020
#define RI_INVPTR                      -900022
#define RI_INVSUB                      -900024
#define RI_ACCVIO                      -900026
#define RI_INTOFLOW                    -900028
#define RI_FLOOFLOW                    -900030
#define RI_FLOUFLOW                     900031
#define RI_INTDIVZERO                  -900032
#define RI_FLODIVZERO                  -900034
#define RI_EOF                         -900035
#define RI_NOTFOUND                    -900037
#define RI_NOROUNDING                  -900039
#define RI_EXTERR                      -900040
#define RI_EXTWARN                     -900041
#define RI_EXTFATAL                    -900042
#define RI_INVTXSTATE                  -900044
#define RI_INVCMD                      -900045
#define RI_UNSUPPCMD                   -900047
#define RI_BUFTOSMALL                  -900048
#define RI_HPARITHTRAP                 -900050
#define RI_REPLAY                       900051
#define RI_INVEXCHANGE                 -900052
#define RI_WAIT_CDB                     900053
#define RI_WAIT_IN_NPSRV                900055
#define RI_WAIT_IN_SRV                  900057
#define RI_WAIT_CL_DELIV                900059
#define RI_WAIT_CL_FIX                  900061
#define RI_WAIT_CL_POS                  900063
#define RI_WAIT_CL_REV_TRADE            900065
#define RI_WAIT_CL_TRADE                900067
#define RI_WAIT_RTR                     900069
#define RI_WAIT_OMDU                    900071
#define RI_ILLEGAL_NODE                -900072
#define RI_INVINT                      -900074
#define RI_NTNOMORE                    -900076
#define RI_NTINVTAB                    -900078
#define RI_NTDUPNAM                    -900080
#define RI_NTNOROOM                    -900082
#define RI_NTNOTFOUND                  -900084
#define RI_NTEXHASH                    -900086
#define RI_NTNOIX                      -900088
#define RI_POSFULL                     -900090
#define RI_POSNOMORE                   -900092
#define RI_POSNOPOINT                  -900094
#define RI_POSUFULL                    -900096
#define RI_TINOVAL                     -900098
#define RI_TIINVTIM                    -900100
#define RI_TIEXPTABFULL                -900102
#define RI_TIVALALEX                   -900103
#define RI_TIIMMTABFULL                -900104
#define RI_HLDINVTYP                   -900106
#define RI_HLDAGREQ                    -900108
#define RI_HLDAGALEX                   -900110
#define RI_HLDAGNOTVALID               -900112
#define RI_HLDNOMEMB                   -900113
#define RI_HLDNOMORE                   -900115
#define RI_HLDPOSALEX                  -900116
#define RI_HLDNOPOS                    -900117
#define RI_HLDNOMAR                    -900119
#define RI_HLDNOMEMMAR                 -900121
#define RI_HLDMARALEX                  -900123
#define RI_HLDNOPRI                    -900125
#define RI_HLDNOMEMPRI                 -900127
#define RI_HLDPRIALEX                  -900129
#define RI_HLDSVALEX                   -900131
#define RI_HLDNOSV                     -900133
#define RI_VALNOVAL                    -900134
#define RI_VALSWNOPER                  -900136
#define RI_REPFMTOFLOW                 -900138
#define RI_MRINVMARK                   -900140
#define RI_MRINVGROUP                  -900142
#define RI_MRINVPARAM                  -900144
#define RI_MRNOPARAM                   -900146
#define RI_MRNOCTRLDEF                 -900148
#define RI_MRNOCORCLA                  -900150
#define RI_MRNOCORSUP                  -900151
#define RI_PRINVMARK                   -900152
#define RI_PRINVGROUP                  -900154
#define RI_PRINVPARAM                  -900156
#define RI_PRNOSYNTHFUT                -900158
#define RI_PRIINVGROUP                 -900160
#define RI_CCTNONODE                   -900162
#define RI_CCTNOMORENOD                -900164
#define RI_CCTNOMOREUNI                -900166
#define RI_CCTTOOMANYPOS               -900168
#define RI_CHFULL                      -900170
#define RI_TDMARFULL                   -900172
#define RI_TDMARALEX                   -900174
#define RI_TDNTDFULL                   -900176
#define RI_TDNTDALEX                   -900178
#define RI_CCTILLEGALMIX               -900180
#define RI_TNMISMATCH                  -900182
#define RI_TNITEXC                     -900184
#define RI_TNILLEGALMIX                -900186
#define RI_TNNODATE                    -900188
#define RI_NOFIX                       -900190
#define RI_QRYUNDEFINED                 900191
#define RI_QRYUNKNOWN                   900193
#define RI_MARG_LIMIT_EXCEEDED         -900195
#define RI_PRICE_LIMIT_EXCEEDED        -900197
#define RI_INVALID_CONFIG_VALUE        -900198
#define RI_HLDFULL                     -900200
#define RI_MRFULL                      -900202
#define RI_MRCORRFULL                  -900204
#define RI_PRFULL                      -900206
#define RI_VALFULL                     -900208
#define RI_HLDNOAG                     -900210
#define RI_CCTFORBIDDENMIX             -900212
#define RI_NTSIZEDIFF                  -900214
#define RI_MRTIERFULL                  -900216
#define RI_MRIMFULL                    -900218
#define RI_MRICFULL                    -900220
#define RI_INVRISKEXP                  -900222
#define RI_INVWROPTMIN                 -900224
#define RI_PRINVSPR                    -900226
#define RI_INVLEG                      -900228
#define RI_PRTICKFULL                  -900230
#define RI_PRSPREADFULL                -900232
#define RI_INVRATIO                    -900234
#define RI_DHNOMOREPOSNOD              -900236
#define RI_DHNOMORERPFNOD              -900238
#define RI_NOFUT                       -900240
#define RI_RCPAR_SYSPALEX              -900242
#define RI_RCPAR_RUNALEX               -900244
#define RI_RCPAR_RUNFULL               -900246
#define RI_RCPAR_SCENALEX              -900248
#define RI_RCPAR_SCENDUPL              -900250
#define RI_RCPAR_NOSCEN                -900252
#define RI_INVDELIV                    -900254
#define RI_VIRTTRADETYPE               -900256
#define RI_NOACC                       -900258
#define RI_IDAYFAIL                    -900260
#define RI_NOCSB                       -900262
#define RI_CSBDUPMEM                   -900264
#define RI_CSBDUPACC                   -900266
#define RI_WAIT_CMS_POS                 900267
#define RI_PRAQRFULL                   -900268
#define RI_PRISNOTQUOTE                -900270
#define RI_TOOMANYLNAM                 -900272
#define RI_CCTDIFFCCY                  -900274
#define RI_BADPARAM                    -900276
#define RI_DB_ERROR                    -900278
#define RI_TOOFEWSURFSRS                900279
#define RI_NOSTRIKELIMIT                900281
#define RI_NRERROR                     -900283
#define RI_VOLASURFMISS                 900285
#define RI_TOOFEWSURFEXP                900287
#define RI_CALIFALLB_OK                 900289
#define RI_CALINOVAL                    900291
#define RI_CALI_NO_ATM                  900293
#define RI_NEG_VOLA                    -900294
#define RI_OMN_NORMAL                   910001
#define RI_OMN_BATNTRN                  910003
#define RI_OMN_NOINFO                   910005
#define RI_OMN_UKNWNQRY                -910006
#define RI_OMN_BADSIZE                 -910008
#define RI_OMN_SNDFAIL                 -910010
#define RI_OMN_BADSEG                  -910012
#define RI_OMN_BADEXCHANGE             -910014
#define RI_OMN_BADMARKET               -910016
#define RI_OMN_NOSUP                   -910018
#define RI_OMN_BADDATE                 -910020
#define RI_OMN_BADSIMVALUE             -910022
#define RI_OMN_BADPRICESIM             -910024
#define RI_OMN_BADVOLVALUE             -910026
#define RI_OMN_BADOLEVEL               -910028
#define RI_OMN_BADSEGMENT              -910030
#define RI_OMN_BADSERIES               -910032
#define RI_OMN_MRPARAM                 -910034
#define RI_OMN_PRPARAM                 -910036
#define RI_OMN_VALINT                  -910038
#define RI_OMN_MRCNTRL                 -910040
#define RI_OMN_GETMTRX                 -910042
#define RI_OMN_MRGMTRX                 -910044
#define RI_OMN_VALFAILED               -910046
#define RI_OMN_SIMDENY                 -910048
#define RI_OMN_SIMNEG                  -910050
#define RI_OMN_SIMNOMTCH               -910052
#define RI_OMN_BADTYPE                 -910054
#define RI_OMN_INVALIDDATES            -910056
#define RI_OMN_INVALIDFLAGS            -910058
#define RI_OMN_INVALIDTRANS            -910060
#define RI_OMN_NOFULLCOLLECT           -910062
#define RI_OMN_NOFUT                   -910064
#define RI_OMN_NOULGPRICE              -910066
#define RI_OMN_TNNODATE                -910068
#define RI_OMN_TNNOKNOWN               -910070
#define RI_OMN_TNNOPRICE               -910072
#define RI_OMN_SWAPNOPRICE             -910074
#define RI_OMN_VALINTPRICE             -910076
#define RI_OMN_NOMVALBOUGHT            -910078
#define RI_OMN_NOMVALSOLD              -910080
#define RI_OMN_NOSPAMRPFPRICE          -910082
#define RI_OMN_VFYERROR                -910084
#define RI_OMN_NOSTMTSTATUS            -910086
#define RI_OMN_NOEXCHANGERATE          -910088
#define RI_OMN_NOEXCHANGERATESRS       -910090
#define RI_OMN_BADPRODUCTAREA          -910092
#define RI_OMN_NOVERIFY                -910094
#define RI_OMN_OPTIONPRICE             -910096
#define RI_OMN_OPTPRICEHIGH            -910098
#define RI_OMN_VOLATILITY              -910100
#define RI_OMN_MSP                     -910102
#define RI_OMN_INTEGRITYFAIL           -910104
#define RI_OMN_NOMEMBER                -910106
#define RI_OMN_NOCLEARINGHOUSE         -910108
#define RI_OMN_NOPSPAMREFPRICE         -910110
#define RI_OMN_NOULGVOLA               -910112
#define RI_OMN_NOCORRMATRIX            -910114
#define RI_OMN_NOLTDPRICE              -910116
#define RI_OMN_NOCASHMBOUGHT           -910118
#define RI_OMN_NOCASHMSOLD             -910120
#define RI_OMN_FWDNOPRICE              -910122
#define RI_OMN_NOUPPERLEVELSRS         -910124
#define RI_OMN_NOSPAMULGPRICE          -910126
#define RI_OMN_ISSUEMARKEDSRS          -910128
#define RI_OMN_RCPARNOSCEN             -910130
#define RI_OMN_RCARWINONLY             -910131
#define RI_OMN_RCARNOSWAPS             -910133
#define RI_OMN_RCPARDIFFSCEN           -910134
#define RI_OMN_RCPARDIFFEXCSCEN        -910136
#define RI_OMN_BADINSDEL               -910138
#define RI_OMN_EXPSERIES               -910140
#define RI_OMN_ZEROQUANTITY            -910142
#define RI_OMN_BADCLOSINGDATE          -910144
#define RI_OMN_BADSTMTDATE             -910146
#define RI_OMN_NONZEROTRADENUMBER      -910148
#define RI_OMN_NOTRADE                 -910150
#define RI_OMN_TRADEDELETED            -910152
#define RI_OMN_RCARDIFFRUNS            -910154
#define RI_OMN_MISCOLPRICE             -910155
#define RI_OMN_CONFIRMEDPRICE          -910156
#define RI_OMN_DBERROR                 -910158
#define RI_OMN_NOOCQ                   -910160
#define RI_OMN_NOVOLA                  -910162
#define RI_OMN_NOASPOROSP              -910164
#define RI_OMN_BADPRICELISTCMD         -910166
#define RI_OMN_NOPRIVATELIST           -910168
#define RI_OMN_BADTRAVALUE             -910170
#define RI_OMN_BADEXPVALUE             -910172
#define RI_OMN_BADFUTVALUE             -910174
#define RI_OMN_BADALARMFLG             -910176
#define RI_OMN_NOFROZENPOS             -910177
#define RI_OMN_PRICESNOTREADY          -910179
#define RI_OMN_SIGNALREADY             -910180
#define RI_OMN_NOMCODEFINED            -910182
#define RI_OMN_NOATYDEFINED            -910183
#define RI_OMN_CALCNBRZERO             -910184
#define RI_OMN_CALLNBRZERO             -910186
#define RI_OMN_NOESPVWV                -910188
#define RI_OMN_BADFIXEDMARGINTYPE      -910190
#define RI_OMN_INVALIDSRS              -910192
#define RI_OMN_NOOPTORFUT              -910194
#define RI_OMN_INVISSUEDATE            -910196
#define RI_OMN_SIMFAILED               -910198
#define RI_MDF_VERSION                  920001

/******************************************************************************
*end*of* ri_messages.h
*******************************************************************************/

#endif /* _RI_MESSAGES_H_ */


#ifndef _RM_MESSAGES_H_
#define _RM_MESSAGES_H_

/******************************************************************************
Module: rm_messages.h

Message definitions generated 2020-10-21 15:24:31 by amt, version 3.19.7.0 - Built: 2017-12-30.

NOTE: Do not edit this file. It is automatically generated from
      one or more message files.
*******************************************************************************/

#define RM_NORMAL                       2000001
#define RM_INTERR                      -2000002
#define RM_FUTBUSDATE                  -2000004
#define RM_BUSNOTTOD                   -2000006
#define RM_INVSTARTDATEFMT             -2000008
#define RM_INVENDDATEFMT               -2000010
#define RM_INVOFFICIALFMT              -2000012
#define RM_PERIODNOTZERO               -2000014
#define RM_INVOFFBATLOG                -2000016
#define RM_BATLOGNOTFND                -2000018
#define RM_TERMSTRUCTCURVENOTFND       -2000020
#define RM_INVBUSDATFMT                -2000022
#define RM_ACCNOTFND                   -2000024
#define RM_SERIESNOTZERO               -2000026
#define RM_SERIESORCURVE               -2000028
#define RM_SERIESNOTFND                -2000030
#define RM_CFMNOTFND                   -2000032
#define RM_STRESSEDCURVENOTFND         -2000034
#define RM_BADMARKET                   -2000036
#define RM_INVISPRELIMINARYFMT         -2000038
#define RM_INVCLHID                    -2000040
#define RM_INVCLHIDPAT                 -2000042
#define RM_INVRUNTYPE                  -2000044
#define RM_INVMRGCLASSFLTR             -2000046
#define RM_INVMRGCLASS                 -2000048
#define RM_INVSEQNO                    -2000050
#define RM_INVCSTBNKIDPAT              -2000052
#define RM_INVACCPAT                   -2000054
#define RM_INVACCPATACCID              -2000056
#define RM_INVACCPATCNTRYID            -2000058
#define RM_INVACCPATCUSTID             -2000060
#define RM_INVCNVCUR                   -2000062
#define RM_INVINCLCURCONVMRGN          -2000064
#define RM_INVINCLPARTPROPMRGN         -2000066
#define RM_INVINCLMRGNCMPINSTRCUR      -2000068
#define RM_INVINCLMRGNCOMPRISKCUR      -2000070
#define RM_INVINCLINFOFLDSINSTRCUR     -2000072
#define RM_INVINCLINFOFLDSRISKCUR      -2000074
#define RM_INVSERIESHAVINGPOS          -2000076
#define RM_SERZEROCNTRY                -2000078
#define RM_SERZEROMRKT                 -2000080
#define RM_SERZEROINSTGRP              -2000082
#define RM_SERZEROMOD                  -2000084
#define RM_SERZEROCOMM                 -2000086
#define RM_SERZEROEXPDATE              -2000088
#define RM_SERZEROSTRIKEPRICE          -2000090
#define RM_SERNOTZEROCNTRY             -2000092
#define RM_SERNOTZEROMRKT              -2000094
#define RM_SERNOTZEROINSTGRP           -2000096
#define RM_SERNOTZEROMOD               -2000098
#define RM_SERNOTZEROCOMM              -2000100
#define RM_SERNOTZEROEXPDATE           -2000102
#define RM_SERNOTZEROSTRIKEPRICE       -2000104
#define RM_INVEXCUSTPAT                -2000106
#define RM_INVINCLALLSERIES            -2000108
#define RM_INVINCLGREEKS               -2000110
#define RM_VERIFYPRICESNOTRUN          -2000112
#define RM_PRICESREADYVERFIYERROR      -2000114
#define RM_NOCONVCURMAR                -2000116
#define RM_INVINSORDEL                 -2000118
#define RM_INVEXCHANGEPAT              -2000120
#define RM_NOEXCHRATEFND               -2000122
#define RM_MORESEGMENT                  2000123
#define RM_INVSEGMENT                  -2000124
#define RM_INVACTIVE                   -2000126
#define RM_INVVALUNTDATEFMT            -2000128
#define RM_INVOWNER                    -2000130
#define RM_INVMAGACCMEM                -2000132
#define RM_NOTSAMECLHMAG               -2000134
#define RM_INVMAGACC                   -2000136
#define RM_INVRMSID                    -2000138
#define RM_INVCUR                      -2000140
#define RM_INVRISKCONV                 -2000142
#define RM_INVGROSSORNET               -2000144
#define RM_INVAGGWHAT                  -2000146
#define RM_INVACCROLE                  -2000148
#define RM_MAGEXIST                    -2000150
#define RM_BADVER                      -2000152
#define RM_ONEITEM                     -2000154
#define RM_MAGNOTFND                   -2000156
#define RM_AGGWHATNOTREQ               -2000158
#define RM_GROSSNETNOTNET              -2000160
#define RM_NOPROPMRA                   -2000162
#define RM_INVPROPMARG                 -2000164
#define RM_INVINSTRORRISKCURR          -2000166
#define RM_INVMAGID                    -2000168
#define RM_INVBASECUR                  -2000170
#define RM_INVPRICECUR                 -2000172
#define RM_INVPRICESCENARIOTYPE        -2000174
#define RM_INVDECINPRICE               -2000176
#define RM_NOITEMS                     -2000178
#define RM_NOTSAMEBASECUR              -2000180
#define RM_MAXMARGINSCENARIO           -2000182
#define RM_MAXCCARSCENARIO             -2000184
#define RM_DUPSCENARIONUMBER           -2000186
#define RM_SCENARIOMUSTBEPOSITIVE      -2000188
#define RM_PRICESIMVALIDATIONFAILURE   -2000190
#define RM_PRICESIMCALCULATIONFAILURE  -2000192
#define RM_PRICESIMSETTINGFAILURE      -2000194
#define RM_CURVENOTFND                 -2000196
#define RM_CURVENOTVAR                 -2000198
#define RM_INVTENORTYPE                -2000200
#define RM_INVTENOR                    -2000202
#define RM_INVDECINDF                  -2000204
#define RM_INVTENORID                  -2000206
#define RM_INVTENORCOMB                -2000208
#define RM_MARGINCLASSNOTVAR           -2000210
#define RM_INVITEMS                    -2000212
#define RM_INVSERIESUSED               -2000214
#define RM_MISSINGTRANSTYPE            -2000216
#define RM_INVTRANSTIME                -2000218
#define RM_INVSESSIONSTATE             -2000220
#define RM_MARKETCLOSED                -2000222
#define RM_INVTRANSMEM                 -2000224
#define RM_INVTRANSCLMEM               -2000226
#define RM_SERIESEXPIRED               -2000228
#define RM_INVACCTYPEMCA               -2000230
#define RM_MULTIPLEFIXADDITIONAL       -2000232
#define RM_FIXADDITIONALNOCURRENCY     -2000234
#define RM_MULTIPLEVARADDITIONALBLANK  -2000236
#define RM_COMBCOMMNOTFND              -2000238
#define RM_MULTIPLEVARADDITIONALCCO    -2000240
#define RM_OUTDATED                    -2000242

/******************************************************************************
*end*of* rm_messages.h
*******************************************************************************/

#endif /* _RM_MESSAGES_H_ */


#ifndef _RX_MESSAGES_H_
#define _RX_MESSAGES_H_

/******************************************************************************
Module: rx_messages.h

Message definitions generated 2020-10-21 15:24:32 by amt, version 3.19.7.0 - Built: 2017-12-30.

NOTE: Do not edit this file. It is automatically generated from
      one or more message files.
*******************************************************************************/

#define RX_USER_BLOCKED                -850002
#define RX_BREACH                      -850004
#define RX_MISSING_ACCOUNT             -850006
#define RX_NO_PTLG                     -850008
#define RX_MISSING_LIMIT               -850010
#define RX_CREDIT_LIMIT_BREACH         -850012
#define RX_POSITION_LIMIT_BREACH       -850014
#define RX_PRICE_LIMIT_BREACH          -850016
#define RX_ORDER_RATE_LIMIT_BREACH     -850018
#define RX_ORDER_QUANTITY_BREACH       -850020
#define RX_ACCOUNT_NONEXIST            -850022
#define RX_ACCOUNT_NOTAVAIL            -850024
#define RX_ACCOUNT_NOTACTIVE           -850026

/******************************************************************************
*end*of* rx_messages.h
*******************************************************************************/

#endif /* _RX_MESSAGES_H_ */


#ifndef _SE_MESSAGES_H_
#define _SE_MESSAGES_H_

/******************************************************************************
Module: se_messages.h

Message definitions generated 2020-10-21 15:24:28 by amt, version 3.19.7.0 - Built: 2017-12-30.

NOTE: Do not edit this file. It is automatically generated from
      one or more message files.
*******************************************************************************/

#define SE_OK                           1000001
#define SE_COMPLETED                    1000003
#define SE_NYI                         -1000005
#define SE_PANIC                       -1000006
#define SE_UKNWNTXN                    -1000008
#define SE_PRTCLERR                    -1000010
#define SE_FAILURE                     -1000012
#define SE_INSUFFARG                   -1000014
#define SE_BADARG                      -1000016
#define SE_INVTRANSIZE                 -1000018
#define SE_INVDATE                     -1000020
#define SE_INVMEMBER                   -1000022
#define SE_TXNOTHANDLED                -1000024
#define SE_DVPNOTFOUND                 -1000026
#define SE_INVSETSTATUS                -1000028
#define SE_NOTCSD                      -1000030
#define SE_INVSETSTATTRANS             -1000032
#define SE_SPECIFICCSD                 -1000034
#define SE_DATENOCHG                   -1000036
#define SE_WRONGSTATE                  -1000038
#define SE_NOFLOW                      -1000040
#define SE_INVACCESS                   -1000042
#define SE_INVDVPITEM                  -1000044
#define SE_INVFIRSTQTY                 -1000046
#define SE_INVSECONDQTY                -1000048
#define SE_INVDVPSUM                   -1000050
#define SE_RCTHOLDING                   1000051
#define SE_ALREXIST                    -1000052
#define SE_NORCTFND                    -1000054
#define SE_INVOPER                     -1000056
#define SE_INVSUBSETSTATDVP            -1000058
#define SE_INVINTMEMBER                -1000060
#define SE_ISINMISSING                 -1000062
#define SE_INVCOMMAND                  -1000064
#define SE_INVCLASS                    -1000066
#define SE_INVEVENT                    -1000068
#define SE_INVPAYNOTENBR               -1000070
#define SE_DELIVNOTFOUND               -1000072
#define SE_ALRINVC                     -1000074
#define SE_ALRDELETED                  -1000076
#define SE_NOTMANUAL                   -1000078
#define SE_INVSETTLPRODUCT             -1000080
#define SE_NOPAYNOTECREATED             1000081
#define SE_DATEPAYED                   -1000082
#define SE_SRVREJECT                   -1000083
#define SE_BALCREATED                  -1000084
#define SE_SQL_ERROR                   -1000086
#define SE_CLHEXCHANGE                 -1000088
#define SE_INVID                       -1000090
#define SE_CODE_EXIST                  -1000092
#define SE_CODE_NOTEXIST               -1000094
#define SE_NOACCOUNTING                -1000096
#define SE_NOTINVOICED                 -1000098
#define SE_INVDELIVERYNBR              -1000100
#define SE_UPDNOTALLOWED               -1000102
#define SE_NOITEMS                     -1000104
#define SE_INVDEBITCREDIT              -1000106
#define SE_JNLNBRMISSING               -1000108
#define SE_RULE_DBERROR                -1000110
#define SE_RULE_DUPRUL                 -1000111
#define SE_RULE_INVALID                -1000113
#define SE_RULE_SANITY                 -1000115
#define SE_ADEUNBALANCE                -1000117
#define SE_NOEXTACC                    -1000118
#define SE_CSDCODEBLANK                -1000120
#define SE_UNKACCFORMAT                -1000122
#define SE_INVPSCLH                    -1000124
#define SE_PAYSYNCH                     1000125
#define SE_INVCURRENCY                 -1000126
#define SE_INSTYPNOTFND                -1000128
#define SE_NOEXTACCCON                 -1000130
#define SE_BICBLANK                    -1000132
#define SE_INVACCOUNT                  -1000133
#define SE_INVEXTACCCONTR              -1000134
#define SE_INVSSTNUM                   -1000136
#define SE_NOMATCHSESSION              -1000138
#define SE_INVVALUATIONDATE            -1000140
#define SE_MISSINGBANKACC              -1000142
#define SE_MISSINGBANK                 -1000144
#define SE_AMOUNTNEG                   -1000146
#define SE_INVPAYMENTCHTYPE            -1000148
#define SE_INVSETBATCHTYPE             -1000150
#define SE_REQQRYNOTGRANTED            -1000152
#define SE_REQUESTNBRZERO              -1000154
#define SE_INVPISTATECHANGE            -1000156
#define SE_REQUESTNBRNOTZERO           -1000158
#define SE_PAYINSTNBRZERO              -1000160
#define SE_DVPALRCREATED               -1000162
#define SE_ACCINPUNBAL                 -1000164
#define SE_ACCUNBAL                    -1000166
#define SE_ACCFAILED                   -1000168
#define SE_OMN_NORMAL                   1004001
#define SE_OMN_BATNTRN                  1004003
#define SE_OMN_NOINFO                   1004005
#define SE_OMN_UNAUTHORIZED             1004007
#define SE_OMN_UKNWNQRY                -1004008
#define SE_OMN_BADSIZE                 -1004010
#define SE_OMN_BADSEG                  -1004012
#define SE_OMN_DB_LOCKED               -1004014
#define SE_OMN_INTERR                  -1004016
#define SE_OMN_INVTIME                 -1004018
#define SE_OMN_BUFOVFLW                -1004019
#define SE_OMN_INVCONFREJ              -1004020
#define SE_OMN_INVDVPACC               -1004022
#define SE_OMN_INVCSDMEM               -1004024
#define SE_OMN_DVPALRDCONF             -1004026
#define SE_OMN_INVUSER                 -1004028
#define SE_OMN_ILLTRANSUSER            -1004030
#define SE_OMN_MEMSUSPCL               -1004032
#define SE_OMN_INVSERIES               -1004034
#define SE_OMN_INSNOTTRADED            -1004036
#define SE_OMN_TRADEDATEPASSED         -1004038
#define SE_OMN_INSISSUSP               -1004040
#define SE_OMN_INVINTMEMBER            -1004042
#define SE_OMN_INTXNDENIED             -1004044
#define SE_OMN_ILLCOMMODITY            -1004046
#define SE_OMN_ILLTRNSTIME             -1004048
#define SE_OMN_INVCONFIRM              -1004050
#define SE_OMN_INVFIRSTDVPACC          -1004052
#define SE_OMN_INVSECONDDVPACC         -1004054
#define SE_OMN_HOLDINGAUTHEXISTS       -1004056
#define SE_OMN_HOLDINGRCTDVPEXISTS     -1004058
#define SE_OMN_DVPCANCELLEDNOCANCEL    -1004060
#define SE_OMN_DVPRECALLEDNOCANCEL     -1004062
#define SE_OMN_DVPCOMPLETEDNOCANCEL    -1004064
#define SE_OMN_MULTUPDDVPNOTALLOWED    -1004066
#define SE_OMN_INV_SETTLEMENT_DATE     -1004068
#define SE_OMN_INV_PAYMENT_DATE        -1004070
#define SE_OMN_INV_SETTLEINSTR_DATE    -1004072
#define SE_OMN_INV_OWNDEAL             -1004074
#define SE_OMN_INV_DIRECTION           -1004076
#define SE_OMN_INV_RULE_TYPE           -1004078
#define SE_OMN_INVACNTTYPE             -1004080
#define SE_OMN_INVPAYPHASE             -1004082
#define SE_OMN_INVPAYSTATE             -1004084
#define SE_OMN_INVPAYNEXTSTATE         -1004086
#define SE_OMN_INVPAYINFOTYPE          -1004088
#define SE_OMN_DIRDELIVNOTIDLE          1004089
#define SE_OMN_INVINTEGRITY            -1004090
#define SE_OMN_INVCLRHOUSE             -1004092
#define SE_OMN_INVDVPTYPE              -1004094
#define SE_OMN_INVCLHID                -1004096
#define SE_OMN_INVISIN                 -1004098
#define SE_OMN_SENOTOPEN               -1004099
#define SE_OMN_INVDVPSEQNBR            -1004100
#define SE_OMN_DVPSETPOSNOTFND         -1004102
#define SE_OMN_DVPNOTCREATED           -1004104
#define SE_OMN_QRYRECLIMREACHED        -1004105
#define SE_MDF_VERSION                  1008001

/******************************************************************************
*end*of* se_messages.h
*******************************************************************************/

#endif /* _SE_MESSAGES_H_ */


#ifndef _SU_MESSAGES_H_
#define _SU_MESSAGES_H_

/******************************************************************************
Module: su_messages.h

Message definitions generated 2020-10-21 15:24:27 by amt, version 3.19.7.0 - Built: 2017-12-30.

NOTE: Do not edit this file. It is automatically generated from
      one or more message files.
*******************************************************************************/

#define SU_NORMAL                       1100001
#define SU_TXALRDHDL                    1100003
#define SU_INVTRANSSIZE                -1100004
#define SU_INVTRANSTYPE                -1100006
#define SU_INV_BLOCK                   -1100007
#define SU_INV_QUANTITY                -1100009
#define SU_INV_PREMIUM                 -1100011
#define SU_INV_OPEN_CLOSE_REQ          -1100013
#define SU_INTERNALERROR               -1100015
#define SU_INVUSER                     -1100017
#define SU_INVTX                       -1100019
#define SU_INVSEGMENTNR                -1100021
#define SU_NOTOPEN                     -1100023
#define SU_FILEOPRFAILED               -1100025
#define SU_INSFMEM                     -1100026
#define SU_BUGCHECK                    -1100028
#define SU_ABORT                       -1100030
#define SU_MATCH_VALIDITY              -1100031
#define SU_PARAMETER_FILEOPRFAILED     -1100032
#define SU_NOT_ACTIVE_BIN              -1100033
#define SU_INVPARAMETER                -1100035
#define SU_INVINSTRCLASS               -1100037
#define SU_INVMM                       -1100039
#define SU_INVPMM                      -1100041
#define SU_NON_CUST_TRADE_LIM_ABS_LOW  -1100043
#define SU_NON_CUST_TRADE_LIM_FRAC_LOW -1100045
#define SU_NON_CUST_TRADE_LIM_FRAC_HIG -1100047
#define SU_FARMM_TRADE_LIM_FRAC_HIGH   -1100049
#define SU_FARMM_TRADE_LIM_FRAC_LOW    -1100051
#define SU_TICK_WORSE_VOLUME_LOW       -1100053
#define SU_DERIVED_ORDER_MAX_SIZE_HIGH -1100055
#define SU_INV_EXPIRATION_GROUP        -1100057
#define SU_INV_STRIKE_PRICE_GROUP      -1100059
#define SU_TIMENOTFUTURE               -1100061
#define SU_ITEMEXIST                   -1100063
#define SU_NOITEMEXIST                 -1100065
#define SU_SERIES_STOPPED_CRS          -1100067
#define SU_COMALRACT                   -1100069
#define SU_COMALRSUS                   -1100071
#define SU_INV_TRADING_STATE           -1100073
#define SU_NO_NEXT_STATE               -1100075
#define SU_INV_DESIGNATED_LIST         -1100077
#define SU_INV_CONCERN_VALUE           -1100079
#define SU_INV_CLASS_FAST_MARKET       -1100081
#define SU_INV_FAST_MARKET_LEVEL       -1100083
#define SU_INVUNDERLYING               -1100085
#define SU_EXPO_LIMIT_FILEOPRFAILED    -1100086
#define SU_CURTAIL_SPR_FACT_LOW        -1100087
#define SU_CURTAIL_SPR_FACT_HIG        -1100089
#define SU_SIGNAL_READY_NOT_ALLWD      -1100091
#define SU_INV_SESS_STATE_ORDER        -1100093
#define SU_EXTCIB_ALREADY_TRIGGERED    -1100095
#define SU_UNKNOWN_EXTCIB              -1100097
#define SU_INV_CODE                    -1100099
#define SU_INV_INFOLEVEL               -1100101
#define SU_INV_INFOTYPE                -1100103
#define SU_INV_PRIO                    -1100105
#define SU_MESSAGE_TOO_LONG            -1100107
#define SU_CORE_NOT_EXISTING           -1100109
#define SU_DEST_NOT_EXISTING           -1100111
#define SU_DATENOTVALID                -1100113
#define SU_TIMENOTVALID                -1100115
#define SU_IS_INV_LASTTRADINGSTATE     -1100117
#define SU_IS_INV_ORDERACTION          -1100119
#define SU_IS_INV_STATUS               -1100121
#define SU_IS_INV_STARTPROC            -1100123
#define SU_IS_INV_STATELEVEL           -1100125
#define SU_IS_SESSIONNOTFOUND          -1100127
#define SU_IS_NONEXTSTATE              -1100129
#define SU_IS_SERIESNOTFOUND           -1100131
#define SU_IS_INV_SESS_STATE_ORDER     -1100133
#define SU_IS_FILLEDNEXTSTATE          -1100135
#define SU_IS_BLANKNEXTSTATE           -1100137
#define SU_INV_TIME_ORDER              -1100139
#define SU_ILL_UPD_STATUS_NOTE         -1100141
#define SU_ILL_SPACE_IN_URL            -1100143
#define SU_ILL_CNTRL_IN_URL            -1100145
#define SU_ILL_MARKET                  -1100147
#define SU_ILL_UNDERLYING              -1100149
#define SU_ILL_SERIES                  -1100151
#define SU_IS_COMBO                    -1100153
#define SU_IS_NOINS                    -1100155
#define SU_IS_TOOFEWITEMS              -1100157
#define SU_IS_TOOMANYITEMS             -1100159
#define SU_UU_USERPEND                 -1100161
#define SU_UU_TIMENOTFUT               -1100163
#define SU_IS_INV_NO_OF_WARNINGS       -1100165
#define SU_INV_URGENT                  -1100167
#define SU_TS_INV_SESS_STATE_ORDER     -1100169
#define SU_TS_INV_TSE_NAME             -1100171
#define SU_INV_TRADING_SESSION         -1100173
#define SU_TS_INV_INST                 -1100175
#define SU_TS_TOOMANYITEMS             -1100177
#define SU_INV_AUCTION_TYPE            -1100179
#define SU_INV_BOOK_TRANSPARANCY       -1100181
#define SU_IS_NOSESS                   -1100183
#define SU_NOT_ISSUER                  -1100185
#define SU_INV_AUCTION_ENDTIME         -1100187
#define SU_INV_ALLOTMENT               -1100189
#define SU_AUCTION_NOTFOUND            -1100191
#define SU_AUCTION_ALR_ACTIVE          -1100193
#define SU_NOT_ENOUGH_TIME_FOR_AUCTION -1100195
#define SU_ISS_HAS_NO_INS              -1100197
#define SU_MDF_VERSION                  1105001

/******************************************************************************
*end*of* su_messages.h
*******************************************************************************/

#endif /* _SU_MESSAGES_H_ */

#endif
