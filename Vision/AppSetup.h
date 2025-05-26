#pragma once

#include <QString>
#include <QWidget>

class AppSetup
{
public:
    /// Pr�pare l�application.  Renvoie true si tout est OK.
    static bool setupApp();

    /// Affiche toutes les infos et warnings emmagasin�es pendant setup.
    static void shareMessages();

    /// Affiche la bo�te de dialogue d�erreur (s�il y a eu �chec).
    static void showError(QWidget* parent = nullptr);

    // Interdire construction / copie
    AppSetup() = delete;
    AppSetup(const AppSetup&) = delete;
    AppSetup& operator=(const AppSetup&) = delete;
};
