#include "Main.h"
#include "Messaging.h"

#pragma region ForwardTest

struct A;

struct B
{
	A* a;
};

struct A
{
	B b;
};

#pragma endregion

int main()
{
	locale::global(locale(""));

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//TestMessaging();
	//TestUserInteract();
	GameLoop();

	return EXIT_SUCCESS;
}

void GameLoop()
{
	const string _actions[] =
	{
		"Inscription",
		"Connexion",
		"Voir les contacts",
		"Ajouter contact",
		"Afficher discussion",
		"Retirer contact",
		"Déconnexion",
		"Désinscription",
		"Quitter"
	};
	const u_int& _actionsCount = sizeof(_actions) / sizeof(const string);
	bool _wantToExit;
	Messaging _messaging;

	DISPLAY("Bienvenue sur ma messagerie !", true);

	do
	{
		DISPLAY("", true);
		const u_int& _actionIndex = RetrieveNumber(_actions, _actionsCount);
		system("cls");
		_wantToExit = !DoAction(_messaging, _actionIndex);

	} while (!_wantToExit);
}

bool DoAction(Messaging& _messaging, const u_int& _actionIndex)
{
	u_int _index;

	switch (_actionIndex)
	{
	case 1:
		_messaging.SignUp();
		break;

	case 2:
		_messaging.SignIn();
		break;

	case 3:
		_messaging.DisplayAllContacts();
		break;

	case 4:
		_messaging.AddContact();
		break;

	case 5:
		_messaging.OpenDiscussion();
		break;

	case 6:
		if (!_messaging.isLogged)
		{
			DISPLAY("Erreur : vous devez être connecté pour faire ceci !", true);
			return false;
		}
		if (_messaging.contactsCount > 0)
		{
			_messaging.DisplayAllContacts();
			_index = AskNumberInRange(1, _messaging.contactsCount, "Quel contact souhaitez-vous retirer ?", true);
			_messaging.RemoveContactByIndex(_index - 1);
		}
		else
		{
			DISPLAY("Vous n'avez pas encore de contact !", true);
		}
		break;

	case 7:
		_messaging.Disconnect();
		break;

	case 8:
		_messaging.Unsubscribe();
		break;

	case 9:
		system("cls");
		DISPLAY("Vous quitter la messagerie !", true);
		return false;

	default:
		system("cls");
		DISPLAY("ERREUR => Index invalide !", true);
		break;
	}

	return true;
}

void TestMessaging()
{
	Messaging _messaging;
	_messaging.DisplayAllContacts();

	_messaging.AddContact();
	_messaging.DisplayAllContacts();
	DISPLAY("", true);
	_messaging.ShowContactDataByName("Michel");
	_messaging.ShowContactDataByName("Marguerite");

	_messaging.AddContact();
	_messaging.AddContact();
	_messaging.DisplayAllContacts();
	DISPLAY("", true);

	_messaging.RemoveContactByIndex(1);
	_messaging.DisplayAllContacts();
	DISPLAY("", true);
	_messaging.ShowContactDataByIndex(1);
	_messaging.ShowContactDataByIndex(0);

	_messaging.ClearContacts();
	_messaging.DisplayAllContacts();
}

void TestUserInteract()
{
	Display("coucou");

	const string _array[2] = { "coucou", "salut" };
	Display(_array, 2, false);

	DISPLAY(RetrieveNumber("donne un nombre stp : ", false), true);
	DISPLAY(RetrieveNumber(_array, 2, false), false);
}