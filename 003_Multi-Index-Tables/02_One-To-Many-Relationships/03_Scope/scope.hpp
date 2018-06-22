#include <eosiolib/eosio.hpp>
#include <eosiolib/singleton.hpp>
#include <eosiolib/print.h>
#include <string>

using namespace eosio;
using namespace std;

class scope : contract {

	public:

		explicit scope(action_name self) : contract(self) {}
		// @abi action
		void signup(const name account);
		// @abi action
		void add(const name account, string itemName);
		// @abi action
		void get(const name account);

	private:
		// @abi table players i64
		struct Profile {
		    name        	account;
		    auto primary_key() const { return account; };
		    EOSLIB_SERIALIZE(Profile, (account));
		};
		// @abi table items i64
		struct Item {
		    uint64_t    	id;
		    string			name;
		    auto primary_key() const { return id; };
		    EOSLIB_SERIALIZE(Item, (id)(name));
		};

		typedef multi_index<N(players), Profile> profile_table;
		typedef multi_index<N(items), Item> item_table;
		typedef singleton<N(totalItems), uint64_t> total_items;

		/**
		 * @brief Increment Item Counter
		 * @author Mitch Pierias <github.com/MitchPierias>
		 */
		uint64_t incrementTotalItems() {
			// Increment our counter if it exists and return
			uint64_t currentCount = total_items::exists() ? total_items::get() + 1 : 0;
			total_items::set(currentCount);
			return currentCount;
		}
};

EOSIO_ABI(scope, (signup)(add)(get));