#pragma once
#include "Contact.h"
#include "UserInteract.h"

struct UserData
{
	string username;
	string password;

	UserData()
	{
		username = "Unknown";
		password = "Unknown";
	}

	UserData(const string& _username, const string& _password)
	{
		username = _username;
		password = _password;
	}
};

struct Messaging
{
	#pragma region Fields

	Contact* contacts;
	u_int contactsCount;
	Contact* owner;
	u_int dataCount;
	UserData* data;
	UserData loggedUser;
	bool isLogged;

	#pragma endregion

	#pragma region Constructors

	Messaging()
	{
		contacts = new Contact[0];
		contactsCount = 0;
		owner = nullptr;
		dataCount = 0;
		data = nullptr;
		loggedUser;
		isLogged = false;
	}
	~Messaging()
	{
		delete[] contacts;
		delete[] data;
		delete owner;
	}

	#pragma endregion

	#pragma region Methods

	#pragma region Un/Subscribe

	void SignIn()
	{
		CLEAR;
		u_int _tryCountMax = 3;
		for (u_int _tryCount = 0; _tryCount <= _tryCountMax; _tryCount++)
		{
			const string& _username = RetrieveText("Entrez un nom d'utilisateur", true);
			const string& _password = RetrieveText("Entrez un mot de passe", true);
			for (u_int _index = 0; _index < dataCount; _index++)
			{
				if (_username == data[_index].username && _password == data[_index].password)
				{
					DISPLAY("Bienvenue !", true);
					isLogged = true;
					loggedUser = data[_index];
					return;
				}
			}
			DISPLAY("Erreur : Nom d'utilisateur ou mot de passe incorrect ! " << _tryCountMax - _tryCount << " essaie restant", true);
		}
		DISPLAY("Erreur : Trop de tentative échoué !", true);
		return;
	}

	void RemoveUserData(UserData& _loggedUser)
	{
		bool _hasFound = false;
		u_int _indexToRemove;
		for (u_int _index = 0; _index < dataCount; _index++)
		{
			if (!_hasFound && data[_index].username == _loggedUser.username)
			{
				_hasFound = true;
				_indexToRemove = _index;
			}
		}
		if (!_hasFound)
		{
			DISPLAY("Erreur : User Introuvable !", true);
		}
		Contact* _newArray = new Contact[--dataCount];
		bool _hasSkip = false;

		for (u_int _index = 0; _index < dataCount; _index++)
		{
			if (!_hasSkip && _index == _indexToRemove)
			{
				_hasSkip = true;
			}
			_newArray[_index] = contacts[_index + _hasSkip];
		}

		delete[] contacts;
		contacts = _newArray;
		isLogged = false;
		_loggedUser;
	}

	void Unsubscribe()
	{
		if (!isLogged)
		{
			DISPLAY("Erreur : vous devez être connecté pour faire ceci !", true);
			return;
		}
		RemoveUserData(loggedUser);
		DISPLAY("Utilisateur supprimé de la base de donnée !", true);
	}

	#pragma endregion

	#pragma region Dis/Connect

	void AddUserData(UserData _newData)
	{
		UserData* _newArray = new UserData[dataCount + 1];

		for (u_int _index = 0; _index < dataCount; _index++)
		{
			_newArray[_index] = data[_index];
		}
		_newArray[dataCount] = _newData;

		delete[] data;
		data = _newArray;
		dataCount++;
	}

	void SignUp()
	{
		CLEAR;
		const string& _username = RetrieveText("Entrez un nom d'utilisateur", true);
		const string& _password = RetrieveText("Entrez un mot de passe", true);
		for (u_int _index = 0; _index < dataCount; _index++)
		{
			if (_username == data[_index].username)
			{
				DISPLAY("Erreur : Nom d'utilisateur déjà pris !", true);
				return;
			}
		}
		UserData _newData = UserData(_username, _password);
		AddUserData(_newData);
	}

	void Disconnect()
	{
		if (!isLogged)
		{
			DISPLAY("Erreur : vous êtes déjà deconnecté !", true);
			return;
		}
		isLogged = false;
		loggedUser;
		DISPLAY("Deconnexion réussie", true);
	}

	#pragma endregion

	#pragma region Show

	void DisplayAllContacts() const
	{
		if (!isLogged)
		{
			DISPLAY("Erreur : vous devez être connecté pour faire ceci !", true);
			return;
		}
		if (contactsCount == 0)
		{
			DISPLAY("Vous n'avez pas encore de contact !", true);
			return;
		}

		DISPLAY("==============", true);
		for (u_int _index = 0; _index < contactsCount; _index++)
		{
			DISPLAY(to_string(_index + 1) + "- " + contacts[_index].name, true);
		}
		DISPLAY("==============", true);
	}
	/// <summary>
	/// Affiche les informations du contact trouvé par son nom
	/// </summary>
	/// <param name="_index">On utilise le nom du contact pour le retrouvé</param>
	/// <returns>Retourne oui si le contact à été trouvé</returns>
	bool ShowContactDataByName(const string& _name) const
	{

		if (Contact* _contact = GetContactByName(_name))
		{
			_contact->Introduce();
			return true;
		}

		return false;
	}
	/// <summary>
	/// Affiche les informations du contact trouvé par son index
	/// </summary>
	/// <param name="_index">On utilise l'index -1 renseigné</param>
	/// <returns>Retourne oui si le contact à été trouvé</returns>
	bool ShowContactDataByIndex(const u_int& _index) const
	{
		if (Contact* _contact = GetContactByIndex(_index - 1))
		{
			_contact->Introduce();
			return true;
		}

		return false;
	}

	void OpenDiscussion()
	{
		if (!isLogged)
		{
			DISPLAY("Erreur : vous devez être connecté pour faire ceci !", true);
			return;
		}
		if (contactsCount <= 0)
		{
			DISPLAY("Vous n'avez pas encore de contact !", true);
			return;
		}

		u_int _contactsCount = 0;
		const string* _contactsName = GetContactsName(_contactsCount);
		Display(_contactsName, _contactsCount, true);
		const u_int& _contactIndex = AskNumberInRange(1, _contactsCount, "Tu veux ouvrir la discussion de quel contact :") - 1;
		system("cls");
		delete[] _contactsName;
		AskActions(_contactIndex);
	}

	#pragma endregion

	#pragma region Interact

	void AskActions(const u_int& _contactIndex)
	{
		bool _wantsToQuit = false;

		do
		{
			const string _actions[] =
			{
				"Afficher discussion",
				"Envoyer un message",
				"Retour"
			};
			const u_int& _actionsCount = sizeof(_actions) / sizeof(const string);
			const u_int& _actionIndex = AskNumberInRange(1, _actionsCount, _actions, _actionsCount);
			_wantsToQuit = !DoActionByIndex(_actionIndex, _contactIndex);

		} while (!_wantsToQuit);
	}

	bool DoActionByIndex(const u_int& _actionIndex, const u_int& _contactIndex)
	{
		switch (_actionIndex)
		{
		case 1:
			// Afficher la conversation avec le contact choisi
			contacts[_contactIndex].ShowDiscussion();
			break;

		case 2:
			// Proposer d'envoyer un message
			SendMessageByIndex(_contactIndex);
			break;

		case 3:
			return false;

		default:
			DISPLAY("ERREUR => Index invalide !", true);
			break;
		}
		
		return true;
	}

	/// <summary>
	/// DEPRECATED
	/// </summary>
	/// <param name="_contactIndex"></param>
	void SuggestToSendMessage(const u_int& _contactIndex)
	{
		DISPLAY("", true);
		if (RetrieveBoolean("Voulez-vous envoyer un message?", true))
		{
			SendMessageByIndex(_contactIndex);
		}
	}

	void SendMessageByIndex(const u_int& _index)
	{
		if (_index < 0 || _index >= contactsCount) return;

		const bool _isSender = RetrieveBoolean("Est-ce que c'est vous qui l'envoyez ?", true);
		Contact* _sender = _isSender ? owner : nullptr;
		contacts[_index].SendMessage(_sender);
	}

	#pragma endregion

	#pragma region Add

	Contact MakeContact()
	{
		CLEAR;
		const string& _name = RetrieveText("Quel est son prénom ?", true);
		const string& _description = RetrieveText("Quel est sa description ?", true);
		return Contact(_name, _description);
	}
	bool AddContact()
	{
		if (!isLogged)
		{
			DISPLAY("Erreur : vous devez être connecté pour faire ceci !", true);
			return false;
		}
		Contact _contact = MakeContact();

		u_int _indexFound;
		if (ExistContact(_contact, _indexFound)) return false;

		Contact* _newArray = new Contact[contactsCount + 1];

		for (u_int _index = 0; _index < contactsCount; _index++)
		{
			_newArray[_index] = contacts[_index];
		}
		_newArray[contactsCount] = _contact;

		delete[] contacts;
		contacts = _newArray;
		contactsCount++;

		return true;
	}

	#pragma endregion

	#pragma region Getters

	string* GetContactsName(u_int& _arraySize) const
	{
		string* _names = new string[0];

		for (u_int _index = 0; _index < contactsCount; _index++)
		{
			AddStringToArray(_names, _arraySize, contacts[_index].name);
		}

		return _names;
	}
	/// <summary>
	/// Retourne l'objet contact grâce à son nom
	/// </summary>
	/// <returns>Contact* afin de savoir s'il a été trouvé</returns>
	Contact* GetContactByName(const string& _name) const
	{
		u_int _indexFound;
		if (!ExistContact(_name, _indexFound))
		{
			DISPLAY("ERREUR => Il impossible de trouver un contact avec le nom \'" + _name + "\' !", true);
			return nullptr;
		}

		return &contacts[_indexFound];
	}
	/// <summary>
	/// Retrouve un contact avec l'index renseigné
	/// </summary>
	/// <param name="_index">Pas u_int parce que le résultat doit pouvoir être négatif</param>
	/// <returns>Retourne le contact trouvé sinon nullptr</returns>
	Contact* GetContactByIndex(const int _index) const
	{
		if (_index < 0)
		{
			DISPLAY("ERREUR => Il impossible de trouver un contact avec un index négatif ou nul !", true);
			return nullptr;
		}
		if (_index >= int(contactsCount))
		{
			DISPLAY("ERREUR => Il impossible de trouver un contact avec l'index " + to_string(_index) + " !", true);
			return nullptr;
		}

		return &contacts[_index];
	}

	#pragma endregion

	#pragma region Check

	bool ExistContact(const Contact& _contact, u_int& _indexFound) const
	{
		_indexFound = -1;

		for (u_int _index = 0; _index < contactsCount; _index++)
		{
			if (IsSameContact(contacts[_index], _contact))
			{
				_indexFound = _index;
				return true;
			}
		}

		return false;
	}
	bool ExistContact(const string& _contactName, u_int& _indexFound) const
	{
		_indexFound = -1;

		for (u_int _index = 0; _index < contactsCount; _index++)
		{
			if (IsSameContact(_contactName, contacts[_index]))
			{
				_indexFound = _index;
				return true;
			}
		}

		return false;
	}
	bool IsSameContact(const Contact& _contact1, const Contact& _contact2) const
	{
		return _contact1.name == _contact2.name
			&& _contact1.name == _contact2.name //TODO change
			&& _contact1.name == _contact2.name;
	}
	bool IsSameContact(const string& _contactName, const Contact& _contact2) const
	{
		return _contactName == _contact2.name;
	}

	#pragma endregion

	#pragma region Remove&Clear

	bool RemoveContactByIndex(const u_int& _indexToRemove)
	{
		if (!GetContactByIndex(_indexToRemove)) return false;

		Contact* _newArray = new Contact[--contactsCount];
		bool _hasSkip = false;

		for (u_int _index = 0; _index < contactsCount; _index++)
		{
			if (!_hasSkip && _index == _indexToRemove)
			{
				_hasSkip = true;
			}
			_newArray[_index] = contacts[_index + _hasSkip];
		}

		delete[] contacts;
		contacts = _newArray;

		return true;
	}
	void ClearContacts()
	{
		delete[] contacts;
		contacts = new Contact[0];
		contactsCount = 0;
	}

	#pragma endregion

	#pragma endregion
};